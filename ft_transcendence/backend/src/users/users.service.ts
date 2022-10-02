import {
  BadRequestException,
  forwardRef,
  Inject,
  Injectable,
} from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { IsDuplicateDto, IsSignedUpDto } from 'src/auth/dto/auth.dto';
import { ChatGateway } from 'src/chat/chat.gateway';
import { ChatLobbyGateway } from 'src/chat/chatLobby.gateway';
import { Repository } from 'typeorm';
import { BlockResultDto } from './dto/blockedUser.dto';
import { GameRecordDto } from './dto/users.dto';
import {
  UpdateUserDto,
  EmailDto,
  SimpleUserDto,
  UserProfileDto,
  WinLoseCountDto,
} from './dto/users.dto';
import { BlockedUser } from './entities/blockedUser.entity';
import { Follow } from './entities/follow.entity';
import { GameRecord } from './entities/gameRecord.entity';
import { User } from './entities/users.entity';
import { UserStatusContainer } from '../userStatus/userStatus.service';

@Injectable()
export class UsersService {
  constructor(
    @InjectRepository(User) private readonly userRepo: Repository<User>,
    @InjectRepository(Follow) private readonly followRepo: Repository<Follow>,
    @InjectRepository(BlockedUser)
    private readonly blockedUserRepo: Repository<BlockedUser>,
    @InjectRepository(GameRecord)
    private readonly gameRecordRepo: Repository<GameRecord>,
    @Inject(forwardRef(() => ChatGateway))
    private readonly chatGateway: ChatGateway,
    @Inject(forwardRef(() => ChatLobbyGateway))
    private readonly chatLobbyGateway: ChatLobbyGateway,
    private readonly userStats: UserStatusContainer,
  ) {}

  async getUsers(): Promise<SimpleUserDto[]> {
    let users = await this.userRepo.find();

    users = users.filter((user) => user.nickname);
    return users.map((user) => {
      return {
        userId: user.id,
        nickname: user.nickname,
        status: this.userStats.getStatus(user.id),
        // status: user.userStatus,
      };
    });
  }

  async getFriends(user: User, userId: number): Promise<SimpleUserDto[]> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    if ((await this.userRepo.findOneBy({ id: userId })) === null) {
      throw new BadRequestException('존재하지 않는 유저 입니다.');
    }

    const friends = await this.followRepo
      .createQueryBuilder('follow')
      .leftJoinAndSelect('follow.follow', 'followee')
      .where('follow.followerId = :userId', { userId })
      .getMany();

    return friends.map((friend) => {
      return {
        userId: friend.follow.id,
        nickname: friend.follow.nickname,
        status: this.userStats.getStatus(friend.follow.id),
        // status: friend.follow.userStatus,
      };
    });
  }

  async getFriendsForEmit(myId: number): Promise<SimpleUserDto[]> {
    const followEntities = await this.followRepo
      .createQueryBuilder('follow')
      .leftJoinAndSelect('follow.follow', 'followee')
      .where('follow.followerId = :myId', { myId })
      .getMany();

    return followEntities.map((followEntity) => {
      return {
        userId: followEntity.follow.id,
        nickname: followEntity.follow.nickname,
        status: this.userStats.getStatus(followEntity.follow.id),
        // status: followEntity.follow.userStatus,
      };
    });
  }

  // 유저가 있을 경우 유저 엔티티를 리턴하고 없을 경우 null을 리턴함
  async getUserByEmail(email: string): Promise<User | null> {
    const ret = await this.userRepo.findOne({ where: { email } });
    return ret;
  }

  // 유저가 있을 경우 유저 엔티티를 리턴하고 없을 경우 null을 리턴함
  async getUserById(id: number): Promise<User | null> {
    const user = await this.userRepo.findOne({ where: { id } });

    return user;
  }

  async getUserProfile(
    user: User,
    myId: number,
    targetId: number,
  ): Promise<UserProfileDto> {
    if (user.id !== myId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    const myUser = await this.getUserById(myId);
    const targetUser = await this.getUserById(targetId);
    if (!myUser || !targetUser) {
      throw new BadRequestException('유저가 존재하지 않습니다.');
    }

    const targetUserWithFollowAndBlock = await this.userRepo
      .createQueryBuilder('user')
      .leftJoinAndSelect('user.follow', 'follow')
      .leftJoinAndSelect('user.blocked', 'blocked')
      .where('user.id = :targetId', { targetId })
      .getOneOrFail();

    return targetUserWithFollowAndBlock.toUserProfileDto(myId);
  }

  async findByNicknameAndUpdateImg(
    userId: number,
    fileName: string,
  ): Promise<string> {
    const serverAddr = process.env.BACKSERVER_ADDR;
    const serverPort = process.env.BACKSERVER_PORT;

    const user = await this.userRepo.findOne({ where: { id: userId } });
    user.avatar = `http://${serverAddr}:${serverPort}/image/${fileName}`;
    await user.save();
    this.chatGateway.updateUserInfoToJoinedChatRooms(user, userId);
    // this.chatGateway.emitChatHistoryToParticipatingChatRooms(userId);
    return user.avatar;
  }

  async createUser(emailDto: EmailDto): Promise<User> {
    const user = new User();
    user.email = emailDto.email;
    // user.userStatus = 'on';

    return await this.userRepo.save(user);
  }

  async isDuplicateNickname(nickname: string): Promise<IsDuplicateDto> {
    const found = await this.userRepo.findOne({ where: { nickname } });

    if (found) {
      return { isDuplicate: true };
    }
    return { isDuplicate: false };
  }

  async addFriend(
    user: User,
    followerId: number,
    followId: number,
  ): Promise<void> {
    if (user.id !== followerId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    const [followerUser, followUser] = await Promise.all([
      this.getUserById(followerId),
      this.getUserById(followId),
    ]);

    if (!followerUser || !followUser) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }
    if (followerId === followId) {
      throw new BadRequestException('자신을 친구추가할 수 없습니다.');
    }

    if (
      (await this.followRepo.findOneBy({
        followerId: followerId,
        followId: followId,
      })) !== null
    ) {
      throw new BadRequestException('이미 팔로우 하는 유저입니다.');
    }

    const follow = new Follow();
    follow.follower = followerUser;
    follow.follow = followUser;

    await this.followRepo.save(follow);
  }

  async removeFriend(user: User, followerId: number, followId: number) {
    if (user.id !== followerId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    const [followerUser, followUser] = await Promise.all([
      this.getUserById(followerId),
      this.getUserById(followId),
    ]);

    if (!followerUser || !followUser) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }

    if ((await this.followRepo.findOneBy({ followerId, followId })) === null) {
      throw new BadRequestException('팔로우 하지 않는 관계입니다.');
    }

    await this.followRepo.delete({ followerId, followId });
  }

  async getGameRecords(userId: number): Promise<GameRecordDto[]> {
    if ((await this.userRepo.findOneBy({ id: userId })) === null) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }

    const gameRecords = await this.gameRecordRepo
      .createQueryBuilder('gameRecord')
      .leftJoinAndSelect('gameRecord.playerOne', 'playerOne')
      .leftJoinAndSelect('gameRecord.playerTwo', 'playerTwo')
      .where('gameRecord.playerOneId = :userId', { userId })
      .orWhere('gameRecord.playerTwoId = :userId', { userId })
      .getMany();

    return gameRecords.map((gameRecord) => gameRecord.toGameRecordDto(userId));
  }

  async updateNickname(
    user: User,
    userId: number,
    nicknameForUpdate: string,
  ): Promise<UserProfileDto> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    if ((await this.userRepo.findOneBy({ id: userId })) === null) {
      throw new BadRequestException('존재하지 않는 유저 입니다.');
    }
    if ((await this.isDuplicateNickname(nicknameForUpdate)).isDuplicate) {
      throw new BadRequestException('이미 존재하는 닉네임 입니다.');
    }

    user.nickname = nicknameForUpdate;
    const updatedUser = await this.userRepo.save(user);

    this.chatGateway.updateUserInfoToJoinedChatRooms(user, userId);
    // this.chatGateway.emitChatHistoryToParticipatingChatRooms(userId);
    this.chatLobbyGateway.emitUserList();
    this.chatLobbyGateway.emitFriendList(userId);

    return updatedUser.toUserProfileDto();
  }

  async getWinLoseCount(userId: number): Promise<WinLoseCountDto> {
    const user = await this.getUserById(userId);
    if (!user) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }

    return user.toWinLoseCount();
  }

  async getBlockedUserById(
    myId: number,
    testingId: number,
  ): Promise<BlockedUser> {
    if (myId === testingId) {
      return null;
    }

    const blocked = await this.blockedUserRepo.findOneBy({
      blockerId: myId,
      blockedId: testingId,
    });

    return blocked;
  }

  async blockUserToggle(
    user: User,
    myId: number,
    targetId: number,
  ): Promise<BlockResultDto> {
    if (user.id !== myId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    const targetUser = await this.userRepo.findOneBy({ id: targetId });

    if (!user || !targetUser) {
      throw new BadRequestException('유저가 존재하지 않습니다.');
    }
    if (myId === targetId) {
      throw new BadRequestException('자신을 차단할 수 없습니다.');
    }

    const block = await this.getBlockedUserById(myId, targetId);

    if (block) {
      await this.blockedUserRepo.delete({ id: block.id });
      this.chatGateway.emitChatHistoryToSocketThatSpecificUserIsParticipating(
        myId,
      );

      return { isBlocked: false };
    } else {
      const friend = await this.followRepo.findOneBy({
        followerId: myId,
        followId: targetId,
      });
      if (friend) {
        await this.followRepo.remove(friend);
      }

      const blockedUserForCreate = new BlockedUser();
      blockedUserForCreate.blockerId = myId;
      blockedUserForCreate.blockedId = targetId;
      await this.blockedUserRepo.save(blockedUserForCreate);

      return { isBlocked: true };
    }
  }

  async getUnblockedUserIds(
    userIdsForCheck: number[],
    senderId: number,
  ): Promise<number[]> {
    const blockerUserIds = (
      await this.blockedUserRepo.findBy({
        blockedId: senderId,
      })
    ).map((blockedUser) => {
      return blockedUser.blockerId;
    });

    const unblockedUserIds = userIdsForCheck.filter(
      (idForCheck) => !blockerUserIds.includes(idForCheck),
    );

    return unblockedUserIds;
  }

  async getFollowerIds(myId: number): Promise<number[]> {
    const followEntities = await this.followRepo.findBy({ followId: myId });

    return followEntities.map((followEntity) => followEntity.followerId);
  }
}
