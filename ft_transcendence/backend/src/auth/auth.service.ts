import {
  BadRequestException,
  forwardRef,
  Inject,
  Injectable,
} from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import axios from 'axios';
import { User } from 'src/users/entities/users.entity';
import { UsersService } from '../users/users.service';
import { EmailService } from '../emails/email.service';
import { IsDuplicateDto, IsSignedUpDto, SecondAuthResultDto } from './dto/auth.dto';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { ConfigService } from '@nestjs/config';
import * as bcrypt from 'bcryptjs';
import { JwtStrategy } from 'src/auth/jwt.strategy';
import { ChatGateway } from 'src/chat/chat.gateway';
import { ChatService } from 'src/chat/chat.service';
import { ChatLobbyGateway } from '../chat/chatLobby.gateway';
import { GameGateway } from 'src/game/game.gateway';

@Injectable()
export class AuthService {
  constructor(
    public readonly configService: ConfigService,
    @Inject(forwardRef(() => UsersService))
    private readonly usersService: UsersService,
    private readonly emailService: EmailService,
    @Inject(forwardRef(() => ChatService))
    private readonly chatService: ChatService,
    @Inject(forwardRef(() => ChatGateway))
    private readonly chatGateway: ChatGateway,
    @Inject(forwardRef(() => ChatLobbyGateway))
    private readonly chatLobbyGateway: ChatLobbyGateway,
    @Inject(forwardRef(() => GameGateway))
    private readonly gameGateway: GameGateway,
    private readonly jwtService: JwtService,
    private readonly jwtStrategy: JwtStrategy,
    @InjectRepository(User) private readonly userRepo: Repository<User>,
  ) {}

  async issueJwt(id: number): Promise<string> {
    const user = await this.usersService.getUserById(id);

    return this.generateUserJwt(user);
  }

  async generateUserJwt(user: User, permit?: string): Promise<string> {
    if (!permit) permit = 'permitted';

    const hashToken = await bcrypt.hash(this.gen6digitCode().toString(), 10);
    const jwt = this.jwtService.sign({
      id: user.id,
      email: user.email,
      accessToken: hashToken,
      permit,
    });
    this.jwtStrategy.setJwtAccessToken(user.id, hashToken);

    return jwt;
  }

  async getAccessToken(code: string): Promise<string> {
    const serverAddr = this.configService.get<string>('BACKSERVER_ADDR');
    const serverPort = this.configService.get<string>('FRONTSERVER_PORT');
    const axiosResult = await axios({
      method: 'post',
      url: `https://api.intra.42.fr/oauth/token`,
      data: {
        grant_type: 'authorization_code',
        client_id:
          process.env.EC2_CLIENT_ID ||
          this.configService.get<string>('42API_UID'),
        client_secret:
          process.env.EC2_CLIENT_SECRET ||
          this.configService.get<string>('42API_SECRET'),
        redirect_uri: `http://${serverAddr}:${serverPort}/callback`,
        code,
      },
    });
    return axiosResult.data.access_token;
  }

  gen6digitCode = (): string => {
    const randNum = Math.floor(Math.random() * 1000000);
    const code = randNum.toString().padStart(6, '0');
    return code;
  };

  async getUserEmail(accessToken: string): Promise<string> {
    const axiosResult = await axios({
      method: 'GET',
      url: 'https://api.intra.42.fr/v2/me',
      headers: {
        authorization: `Bearer ${accessToken}`,
      },
    });

    const { email } = axiosResult.data;
    return email;
  }

  userToIsSignedUpDto(user: User, jwt: string): IsSignedUpDto {
    const isSignedUpDto = new IsSignedUpDto();

    isSignedUpDto.userId = user.id;
    isSignedUpDto.nickname = user.nickname;
    isSignedUpDto.email = user.email;
    isSignedUpDto.avatar = user.avatar;
    isSignedUpDto.isSecondAuthOn = user.isSecondAuthOn;
    isSignedUpDto.jwt = jwt;

    return isSignedUpDto;
  }

  async emitUpdatedUserList(userId: number, user?: User): Promise<void> {
    if (!user) user = await this.usersService.getUserById(userId);
    if (!user) return;

    console.log('emitUpdatedUserList');
    console.log('emitUpdatedUserList');
    const participatingChatRooms =
      await this.chatService.getParticipatingChatRooms(user, user.id);

    participatingChatRooms.forEach((participatingChatRoom) => {
      const chatRoomUserDtos = this.chatGateway.emitChatRoomParticipants(
        participatingChatRoom.roomId.toString(),
      );
      this.gameGateway.broadcastToLobby(
        'updateChatRoomParticipants',
        chatRoomUserDtos,
      );
    });

    this.chatGateway.emitFriendList(user.id);
    let userList = await this.chatLobbyGateway.emitUserList();
    userList = userList.filter((user) => user.nickname);
    this.chatLobbyGateway.emitFriendList(user.id);
    this.gameGateway.broadcastToLobby('updateUserList', userList);
  }

  async isSignedUp(code: string): Promise<IsSignedUpDto> {
    const accessToken = await this.getAccessToken(code);
    const userEmail = await this.getUserEmail(accessToken);

    let user = await this.usersService.getUserByEmail(userEmail);
    let jwt: string = null;

    if (!user) {
      user = await this.usersService.createUser({
        email: userEmail,
      });
    }

    if (user.isSecondAuthOn === false) jwt = await this.generateUserJwt(user);
    else jwt = await this.generateUserJwt(user, 'temporary');

    return this.userToIsSignedUpDto(user, jwt);
  }

  async isDuplicateNickname(nickname: string): Promise<IsDuplicateDto> {
    if (nickname.length < 2 || nickname.length > 8) {
      throw new BadRequestException('닉네임은 최소2자 최대 8자 입니다.');
    }

    return await this.usersService.isDuplicateNickname(nickname);
  }

  async logoutStatus(user: User, userId: number): Promise<void> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    this.jwtStrategy.deletejwtAccessToken(user.id);
  }

  async startSecondAuth(
    user: User,
    id: number,
    email: string,
  ): Promise<boolean> {
    if (user.id !== id) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    if (user === null) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }

    const code = this.gen6digitCode();
    const salt = await bcrypt.genSalt();
    const hashedCode = await bcrypt.hash(code, salt);
    user.secondAuthEmail = email;
    user.secondAuthCode = hashedCode;

    await user.save();
    await this.emailService.sendEmail(email, code);
    return true;
  }

  async verifySecondAuth(
    userOfJwt: User,
    id: number,
    code: string,
  ): Promise<SecondAuthResultDto> {
    // if (userOfJwt.id !== id) {
    //   throw new BadRequestException('잘못된 유저의 접근입니다.');
    // }
    const user = await this.usersService.getUserById(id);
    if (user === null) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }
    const result = new SecondAuthResultDto();

    if (await bcrypt.compare(code, user.secondAuthCode)) {
      user.secondAuthCode = '7777777';
      await user.save();
      result.isOk = true;
    } else {
      result.isOk = false;
    }
    if (user.isSecondAuthOn === true && result.isOk === true)
      result.jwt = await this.generateUserJwt(user);
    else result.jwt = null;

    return result;
  }

  async enrollSecondAuth(user: User, id: number): Promise<void> {
    if (user.id !== id) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    if (user === undefined) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }
    if (user.isSecondAuthOn === true) {
      throw new BadRequestException('이미 등록된 유저입니다.');
    }
    if (user.secondAuthCode !== '7777777') {
      throw new BadRequestException('인증되지 않은 유저입니다.');
    }

    user.isSecondAuthOn = true;
    await user.save();
  }

  async disableSecondAuth(user: User, id: number): Promise<void> {
    if (user.id !== id) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    if (user === undefined) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }

    user.secondAuthEmail = null;
    user.secondAuthCode = null;
    user.isSecondAuthOn = false;
    await user.save();
  }

  async shootSecondAuth(users: User, id: number): Promise<boolean> {
    const user = await this.usersService.getUserById(id);
    // if (users.id !== user.id)
    //   throw new BadRequestException('권한이 없는 유저입니다.');

    if (user === null) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }
    if (user.isSecondAuthOn === false) {
      throw new BadRequestException('2차 인증을 설정하지 않은 유저입니다.');
    }

    const code = this.gen6digitCode();
    const salt = await bcrypt.genSalt();
    const hashedCode = await bcrypt.hash(code, salt);
    user.secondAuthCode = hashedCode;
    await user.save();

    await this.emailService.sendEmail(user.secondAuthEmail, code);
    return true;
  }
}
