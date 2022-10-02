import {
  BadRequestException,
  ForbiddenException,
  forwardRef,
  Inject,
  Injectable,
  Logger,
} from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { BlockedUser } from 'src/users/entities/blockedUser.entity';
import { User } from 'src/users/entities/users.entity';
import { DataSource, Repository } from 'typeorm';
import { ChatGateway } from './chat.gateway';
import {
  ChatRoomDataDto,
  SetChatRoomDto,
  ChatRoomIdDto,
  ChatRoomDto,
} from './dto/chatRoom.dto';
import {
  ParticipantRoleDto,
  ChatRoomUserDto,
  IsMutedDto,
  ChatParticipantProfileDto,
} from './dto/chatParticipant.dto';
import { ChatContentDto, MessageDto } from './dto/chatContents.dto';
import { ChatContents } from './entities/chatContents.entity';
import { ChatParticipant } from './entities/chatParticipant.entity';
import { ChatRoom as ChatRoom } from './entities/chatRoom.entity';
import * as bcrypt from 'bcryptjs';
import { SchedulerRegistry } from '@nestjs/schedule';
import { ChatLobbyGateway } from './chatLobby.gateway';
import { UserStatusContainer } from 'src/userStatus/userStatus.service';

@Injectable()
export class ChatService {
  constructor(
    @InjectRepository(ChatContents)
    private readonly chatContentsRepo: Repository<ChatContents>,
    @InjectRepository(ChatParticipant)
    private readonly chatParticipantRepo: Repository<ChatParticipant>,
    @InjectRepository(ChatRoom)
    private readonly chatRoomRepo: Repository<ChatRoom>,
    @Inject(forwardRef(() => ChatGateway))
    private readonly chatGateway: ChatGateway,
    @Inject(forwardRef(() => ChatLobbyGateway))
    private readonly chatLobbyGateway: ChatLobbyGateway,
    @InjectRepository(User)
    private readonly userRepo: Repository<User>,
    private dataSource: DataSource,
    @InjectRepository(BlockedUser)
    private readonly blockedUserRepo: Repository<BlockedUser>,
    private readonly schedulerRegistry: SchedulerRegistry,
    @Inject(forwardRef(() => UserStatusContainer))
    private readonly userStats: UserStatusContainer,
  ) {}

  private logger: Logger = new Logger('ChatService');

  async getChatRoomById(id: number): Promise<ChatRoom> {
    const chatRoom = await this.chatRoomRepo.findOneOrFail({ where: { id } });

    return chatRoom;
  }

  async getChatRoomData(roomId: number): Promise<ChatRoomDataDto> {
    const chatRoom = await this.chatRoomRepo.findOne({ where: { id: roomId } });

    if (!chatRoom) {
      throw new BadRequestException('존재하지 않는 채팅방입니다.');
    }
    const chatRoomData = new ChatRoomDataDto();
    chatRoomData.roomId = roomId;
    chatRoomData.title = chatRoom.title;
    chatRoomData.ownerId = chatRoom.ownerId;
    chatRoomData.isDm = chatRoom.isDm;

    return chatRoomData;
  }

  async getChatRooms(): Promise<ChatRoomDto[]> {
    let chatRooms = await this.chatRoomRepo
      .createQueryBuilder('chatRoom')
      .leftJoinAndSelect('chatRoom.chatParticipant', 'chatParticipant')
      .getMany();

    chatRooms = chatRooms.filter((chatRoom) => !chatRoom.isDm);

    return chatRooms.map((chatRoom) => {
      return chatRoom.toChatRoomDto();
    });
  }

  async getRoomParticipants(roomId: number): Promise<ChatRoomUserDto[]> {
    if (!(await this.chatRoomRepo.findOneBy({ id: roomId }))) {
      throw new BadRequestException('존재하지 않는 채팅방 입니다.');
    }

    const chatParticipants = await this.chatParticipantRepo
      .createQueryBuilder('chatParticipant')
      .leftJoinAndSelect('chatParticipant.user', 'user')
      .where('chatParticipant.chatRoomId = :roomId', { roomId })
      .andWhere('chatParticipant.isBanned = false')
      .getMany();

    return chatParticipants.map((chatParticipant) => {
      const chatRoomUserDto = new ChatRoomUserDto();
      chatRoomUserDto.userId = chatParticipant.userId;
      chatRoomUserDto.nickname = chatParticipant.user.nickname;
      chatRoomUserDto.status = this.userStats.getStatus(chatParticipant.userId);
      // chatRoomUserDto.status = chatParticipant.user.userStatus;
      chatRoomUserDto.role = chatParticipant.role;

      return chatRoomUserDto;
    });
  }

  async banUser(
    user: User,
    roomId: number,
    callingUserId: number,
    targetUserId: number,
  ): Promise<void> {
    if (user.id !== callingUserId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    const room = await this.chatRoomRepo.findOneBy({ id: roomId });
    if (!room) {
      throw new BadRequestException('채팅방이 존재하지 않습니다.');
    }
    const targetChatParticipant = await ChatParticipant.findOneBy({
      userId: targetUserId,
      chatRoomId: roomId,
    });
    if (!targetChatParticipant) {
      throw new BadRequestException('존재하지 않는 참여자입니다.');
    }
    if (targetChatParticipant.isBanned) {
      throw new BadRequestException('이미 강퇴당한 유저입니다.');
    }
    if (room.isDm === true) {
      throw new BadRequestException('DM방 입니다.');
    }
    if (targetChatParticipant.role === 'owner') {
      throw new BadRequestException('방장을 강퇴할 수 없습니다.');
    }
    const callingChatParticipant = await ChatParticipant.findOneBy({
      userId: callingUserId,
      chatRoomId: roomId,
    });
    if (callingChatParticipant.role === 'guest') {
      throw new BadRequestException('권한이 없는 사용자입니다.');
    }
    targetChatParticipant.isBanned = true;
    await targetChatParticipant.save();

    // 강퇴 취소 스케줄러
    this.addBanTimeout(
      `banTimeout${targetChatParticipant.id}`,
      10 * 1000,
      targetChatParticipant,
    );

    // 강퇴 메세지 db에 저장
    const { id: createdChatContentId } = await this.chatContentsRepo.save({
      chatRoomId: roomId,
      userId: targetUserId,
      content: `님이 10초 동안 강퇴당했습니다.`,
      isNotice: true,
    });

    // 채널 유저들에게 강퇴 메세지 전송
    this.chatGateway.sendNoticeMessage(
      roomId,
      await this.getChatContentDtoForEmit(createdChatContentId),
    );
    this.chatGateway.emitChatRoomParticipants(roomId.toString());
    this.chatGateway.disconnectUser(roomId, targetUserId);
  }

  async kickUser(
    user: User,
    roomId: number,
    callingUserId: number,
    targetUserId: number,
  ) {
    if (user.id !== callingUserId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    const room = await this.chatRoomRepo.findOneBy({ id: roomId });
    if (!room) {
      throw new BadRequestException('채팅방이 존재하지 않습니다.');
    }
    const targetChatParticipant = await ChatParticipant.findOneBy({
      userId: targetUserId,
      chatRoomId: roomId,
    });
    if (!targetChatParticipant) {
      throw new BadRequestException('존재하지 않는 참여자입니다.');
    }
    if (targetChatParticipant.isBanned) {
      throw new BadRequestException('이미 강퇴당한 유저입니다.');
    }
    if (room.isDm === true) {
      throw new BadRequestException('DM방 입니다.');
    }
    if (targetChatParticipant.role === 'owner') {
      throw new BadRequestException('방장을 강퇴할 수 없습니다.');
    }
    const callingChatParticipant = await ChatParticipant.findOneBy({
      userId: callingUserId,
      chatRoomId: roomId,
    });
    if (callingChatParticipant.role === 'guest') {
      throw new BadRequestException('권한이 없는 사용자입니다.');
    }
    console.log('\n ### 2');

    await this.chatParticipantRepo.remove(targetChatParticipant);

    // 강퇴 메세지 db에 저장
    const { id: createdChatContentId } = await this.chatContentsRepo.save({
      chatRoomId: roomId,
      userId: targetUserId,
      content: `님이 강퇴당했습니다.`,
      isNotice: true,
    });
    console.log('\n ### 3');

    // 채널 유저들에게 강퇴 메세지 전송
    this.chatGateway.sendNoticeMessage(
      roomId,
      await this.getChatContentDtoForEmit(createdChatContentId),
    );
    this.chatGateway.emitChatRoomParticipants(roomId.toString());
    this.chatGateway.disconnectUser(roomId, targetUserId);
    console.log('\n ### 4');
  }

  async getParticipatingChatRooms(
    user: User,
    userId: number,
  ): Promise<ChatRoomDto[]> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    let chatRooms = await this.chatRoomRepo
      .createQueryBuilder('chatRoom')
      .leftJoinAndSelect('chatRoom.chatParticipant', 'chatParticipant')
      .where('chatParticipant.isBanned = false')
      .getMany();

    chatRooms = chatRooms.filter((chatRoom) => {
      const chatParticipantIds = chatRoom.chatParticipant.map(
        (chatParticipant) => chatParticipant.userId,
      );
      if (chatParticipantIds.includes(userId)) {
        return true;
      }
      return false;
    });

    return chatRooms.map((chatRoom) => {
      return chatRoom.toChatRoomDto();
    });
  }

  async addUserToChatRoom(
    chatRoomId: number,
    userId: number,
    role: 'owner' | 'manager' | 'guest',
  ) {
    const chatParticipant = new ChatParticipant();
    chatParticipant.role = role;
    chatParticipant.chatRoomId = chatRoomId;
    chatParticipant.userId = userId;

    await this.chatParticipantRepo.save(chatParticipant);
  }

  async createChatRoom(
    user: User,
    userId: number,
    createChatRoomDto: SetChatRoomDto,
  ): Promise<ChatRoomDataDto> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    const chatRoom = new ChatRoom();
    chatRoom.title = createChatRoomDto.title;
    if (createChatRoomDto.password) {
      const salt = await bcrypt.genSalt();
      const hashedPassword = await bcrypt.hash(
        createChatRoomDto.password,
        salt,
      );
      chatRoom.password = hashedPassword;
    }
    chatRoom.ownerId = userId;

    const createdChatRoom = await this.chatRoomRepo.save(chatRoom);

    await this.addUserToChatRoom(
      createdChatRoom.id,
      createdChatRoom.ownerId,
      'owner',
    );

    // 입장 메세지 db에 저장
    await this.chatContentsRepo.save({
      chatRoomId: createdChatRoom.id,
      userId,
      content: `님이 입장 하셨습니다.`,
      isNotice: true,
    });

    const chatRoomDataDto = new ChatRoomDataDto();
    chatRoomDataDto.roomId = createdChatRoom.id;
    chatRoomDataDto.title = createdChatRoom.title;
    chatRoomDataDto.ownerId = createdChatRoom.ownerId;
    chatRoomDataDto.isDm = createdChatRoom.isDm;

    this.chatGateway.emitChatRoomParticipants(createdChatRoom.id.toString());
    this.chatLobbyGateway.emitChatRoomList();
    this.chatLobbyGateway.emitParticipantingChatRoomList(createdChatRoom.id);
    return chatRoomDataDto;
  }

  // 채팅방이 존재할 경우 채팅방 엔티티를 리턴하고 존재하지 않을 경우 null을 리턴함
  async isExistChatRoom(roomId: number): Promise<ChatRoom | null> {
    return await this.chatRoomRepo.findOneBy({ id: roomId });
  }

  async isCorrectPasswordOfChatRoom(
    roomId: number,
    roomPassword: string | null,
  ): Promise<boolean> {
    const room = await this.isExistChatRoom(roomId);

    if (!room) {
      throw new BadRequestException('존재하지 않는 채팅방 입니다.');
    }
    if (!room.password) {
      return true;
    }
    if (room.password && !roomPassword) {
      throw new BadRequestException('비밀번호를 입력해 주세요.');
    }
    if (await bcrypt.compare(roomPassword, room.password)) {
      return true;
    }
    return false;
  }

  // 채팅방 참여자일 경우 chatParticipant 엔티티 리턴, 참여자가 아닐 경우 null 리턴, 차단된 유저일 경우 403리턴
  async isExistMember(roomId: number, userId: number) {
    const chatParticipant = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId,
    });

    if (chatParticipant && chatParticipant.isBanned) {
      throw new ForbiddenException('강퇴당한 유저입니다.');
    }

    return chatParticipant;
  }

  async getChatContentDtoForEmit(
    chatContentId: number,
  ): Promise<ChatContentDto> {
    const createdChatcontent = await this.chatContentsRepo
      .createQueryBuilder('chatContent')
      .leftJoinAndSelect('chatContent.user', 'user')
      .where('chatContent.id = :chatContentId', {
        chatContentId,
      })
      .getOne();

    return createdChatcontent.toChatContentDto();
  }

  async enterChatRoom(
    user: User,
    roomId: number,
    userId: number,
    roomPassword: string | null,
  ): Promise<ChatRoomIdDto> {
    if (!(await this.isExistMember(roomId, userId))) {
      if (!(await this.isCorrectPasswordOfChatRoom(roomId, roomPassword))) {
        throw new BadRequestException('채팅방의 비밀번호가 일치하지 않습니다.');
      }
      if (user.id !== userId) {
        throw new BadRequestException('잘못된 유저의 접근입니다.');
      }
      const chatParticipant = new ChatParticipant();
      chatParticipant.chatRoomId = roomId;
      chatParticipant.userId = userId;
      await this.chatParticipantRepo.save(chatParticipant);

      // 입장 메세지 db에 저장
      const { id: createdChatContentId } = await this.chatContentsRepo.save({
        chatRoomId: roomId,
        userId: user.id,
        content: `님이 입장 하셨습니다.`,
        isNotice: true,
      });

      // 채널 유저들에게 입장 메세지 전송
      this.chatGateway.sendNoticeMessage(
        roomId,
        await this.getChatContentDtoForEmit(createdChatContentId),
      );
    }

    this.chatGateway.emitChatRoomParticipants(roomId.toString());
    this.chatLobbyGateway.emitChatRoomList();
    this.chatLobbyGateway.emitParticipantingChatRoomList(roomId);
    return { roomId: roomId };
  }

  async updateRoom(
    roomId: number,
    ownerId: number,
    updateChatRoomDto: SetChatRoomDto,
  ): Promise<ChatRoomDataDto> {
    const room = await this.chatRoomRepo.findOneBy({ id: roomId });
    if (!room) {
      throw new BadRequestException('채팅방이 존재하지 않습니다.');
    }
    if (room.ownerId !== ownerId) {
      throw new BadRequestException(
        '채팅방의 소유자만 방 설정을 변경할 수 있습니다.',
      );
    }

    room.title = updateChatRoomDto.title;
    if (updateChatRoomDto.password) {
      const salt = await bcrypt.genSalt();
      const hashedPassword = await bcrypt.hash(
        updateChatRoomDto.password,
        salt,
      );
      room.password = hashedPassword;
    } else room.password = null;

    const updatedRoom = await this.chatRoomRepo.save(room);
    this.chatGateway.emitChatRoomTitle(
      updatedRoom.id.toString(),
      updatedRoom.title,
    );

    this.chatLobbyGateway.emitChatRoomList();
    this.chatLobbyGateway.emitParticipantingChatRoomList(roomId);
    return updatedRoom.toChatRoomDataDto();
  }

  async exitRoom(user: User, roomId: number, userId: number): Promise<void> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    const room = await this.chatRoomRepo.findOneBy({ id: roomId });
    if (!room) {
      throw new BadRequestException('채팅방이 존재하지 않습니다.');
    }

    const chatParticipant = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId,
    });

    if (!chatParticipant) {
      throw new BadRequestException('참여중인 채팅방이 아닙니다.');
    }

    if (room.isDm) {
      userId = room.ownerId;
    }

    if (room.ownerId === userId) {
      // 방 폭파 + 방에서 다 내보내기
      this.chatGateway.wss.to(roomId.toString()).emit('disconnectSocket', null);
      this.chatGateway.wss.to(roomId.toString()).disconnectSockets();
      await this.chatRoomRepo.delete({ id: roomId });
    } else {
      await this.chatParticipantRepo.delete({ chatRoomId: roomId, userId });

      // 퇴장 메세지 db에 저장
      const { id: createdChatContentId } = await this.chatContentsRepo.save({
        chatRoomId: roomId,
        userId: user.id,
        content: `님이 퇴장 하셨습니다.`,
        isNotice: true,
      });

      // 채널 유저들에게 퇴장 메세지 전송
      this.chatGateway.sendNoticeMessage(
        roomId,
        await this.getChatContentDtoForEmit(createdChatContentId),
      );

      this.chatGateway.emitChatRoomParticipants(roomId.toString());
    }

    this.chatLobbyGateway.emitChatRoomList();
    this.chatLobbyGateway.emitParticipantingChatRoomList();
  }

  async toggleParticipantRole(
    roomId: number,
    callingUserId: number,
    targetUserId: number,
  ): Promise<ParticipantRoleDto> {
    const room = await this.chatRoomRepo.findOneBy({ id: roomId });
    if (!room) {
      throw new BadRequestException('채팅방이 존재하지 않습니다.');
    }

    const chatParticipants: ChatParticipant[] =
      await this.chatParticipantRepo.find({
        where: [{ chatRoomId: roomId }],
      });
    const targetParticipant: ChatParticipant = chatParticipants.find(
      (participant) => participant.userId === targetUserId,
    );
    const callingParticipant: ChatParticipant = chatParticipants.find(
      (participant) => participant.userId === callingUserId,
    );

    if (!targetParticipant) {
      throw new BadRequestException('존재하지 않는 참여자입니다.');
    }

    if (targetParticipant.role === 'guest') {
      if (callingParticipant.role === 'guest') {
        throw new BadRequestException('변경 권한이 없습니다.');
      }
      targetParticipant.role = 'manager';
    } else if (targetParticipant.role === 'manager') {
      if (callingParticipant.role !== 'owner') {
        throw new BadRequestException('변경 권한이 없습니다.');
      }
      targetParticipant.role = 'guest';
    } else {
      throw new BadRequestException('Owner는 절대권력 입니다.');
    }
    await targetParticipant.save();

    this.chatGateway.emitRole(
      roomId.toString(),
      targetParticipant.userId.toString(),
      targetParticipant.role,
    );

    this.chatGateway.wss
      .to(roomId.toString())
      .emit('updateUserList', targetParticipant);

    const result: ParticipantRoleDto = new ParticipantRoleDto();
    result.role = targetParticipant.role;
    return result;
  }

  async muteCertainParticipant(
    user: User,
    roomId: number,
    callingUserId: number,
    targetUserId: number,
  ): Promise<IsMutedDto> {
    if (user.id !== callingUserId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }

    const room = await this.chatRoomRepo.findOneBy({ id: roomId });
    if (!room) {
      throw new BadRequestException('채팅방이 존재하지 않습니다.');
    }

    const callingChatParticipant = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId: callingUserId,
    });
    if (callingChatParticipant.role === 'guest') {
      throw new BadRequestException('음소거 권한이 없습니다.');
    }

    const chatParticipants: ChatParticipant[] =
      await this.chatParticipantRepo.find({
        where: [{ chatRoomId: roomId }],
      });
    const targetChatParticipant: ChatParticipant = chatParticipants.find(
      (participant) => participant.userId === targetUserId,
    );

    if (!targetChatParticipant) {
      throw new BadRequestException('존재하지 않는 참여자입니다.');
    }
    if (targetChatParticipant.role === 'owner') {
      throw new BadRequestException('방장을 음소거 시킬 수 없습니다.');
    }

    if (targetChatParticipant.isMuted) {
      targetChatParticipant.isMuted = false;
      this.deleteMuteTimeout(`muteTimeout${targetChatParticipant.id}`);

      // 음소거 해제 메세지 db에 저장
      const { id: createdChatContentId } = await this.chatContentsRepo.save({
        chatRoomId: targetChatParticipant.chatRoomId,
        userId: targetChatParticipant.userId,
        content: `님의 채팅 금지가 해제되었습니다.`,
        isNotice: true,
      });

      // 채널 유저들에게 음소거해제 메세지 전송
      this.chatGateway.sendNoticeMessage(
        targetChatParticipant.chatRoomId,
        await this.getChatContentDtoForEmit(createdChatContentId),
      );
    } else {
      targetChatParticipant.isMuted = true;
      this.addMuteTimeout(
        `muteTimeout${targetChatParticipant.id}`,
        10 * 1000,
        targetChatParticipant,
      );

      // 음소거 메세지 db에 저장
      const { id: createdChatContentId } = await this.chatContentsRepo.save({
        chatRoomId: targetChatParticipant.chatRoomId,
        userId: targetChatParticipant.userId,
        content: `님은 10초 동안 채팅이 금지되었습니다.`,
        isNotice: true,
      });

      // 채널 유저들에게 음소거해제 메세지 전송
      this.chatGateway.sendNoticeMessage(
        targetChatParticipant.chatRoomId,
        await this.getChatContentDtoForEmit(createdChatContentId),
      );
    }
    await targetChatParticipant.save();

    this.chatGateway.wss
      .to(roomId.toString())
      .emit('updateUserList', targetChatParticipant);

    const result: IsMutedDto = new IsMutedDto();
    result.isMuted = targetChatParticipant.isMuted;
    return result;
  }

  async createChatContent(
    userId: number,
    roomId: number,
    msg: string,
  ): Promise<ChatContentDto> {
    const user = await this.userRepo.findOneBy({ id: userId });
    if (!user) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }
    const room = await this.chatRoomRepo.findOneBy({ id: roomId });
    if (!room) {
      throw new BadRequestException('존재하지 않는 채팅방입니다.');
    }

    const { id: createdChatContentId } = await this.chatContentsRepo.save({
      chatRoomId: roomId,
      userId,
      content: msg,
    });

    return await this.getChatContentDtoForEmit(createdChatContentId);
  }

  async isMessageFromBlockedUser(
    blockerId: number,
    blockedId: number,
  ): Promise<boolean> {
    const found = await this.blockedUserRepo.findOneBy({
      blockerId,
      blockedId,
    });

    if (found) {
      return true;
    }
    return false;
  }

  async submitChatContent(
    user: User,
    roomId: number,
    userId: number,
    messageDto: MessageDto,
  ): Promise<void> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    if (
      !(await this.chatParticipantRepo.findOneBy({
        chatRoomId: roomId,
        userId: userId,
      }))
    ) {
      throw new BadRequestException('잘못된 유저나 채팅방입니다.');
    }
    //채팅 DB에 저장
    const chatContents = new ChatContents();
    chatContents.chatRoomId = roomId;
    chatContents.userId = userId;
    chatContents.content = messageDto.message;
    await this.chatContentsRepo.save(chatContents);
    //전체에 emit
    // this.chatGateway.wss.to(roomId.toString()).emit('updateChat', messageDto);
  }

  async enterDmRoom(
    user: User,
    myId: number,
    partnerId: number,
  ): Promise<ChatRoomIdDto> {
    if (user.id !== myId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    const chatRooms = await this.chatRoomRepo
      .createQueryBuilder('chatRoom')
      .leftJoinAndSelect('chatRoom.chatParticipant', 'chatParticipant')
      .where('chatRoom.isDm = true')
      .andWhere('(chatRoom.ownerId = :myId or chatRoom.ownerId = :partnerId)', {
        myId,
        partnerId,
      })
      .getMany();

    const chatRoom = chatRooms.find((chatRoom) => {
      let isCorrectMember = 0;

      chatRoom.chatParticipant.forEach((person) => {
        if (person.userId === myId || person.userId === partnerId) {
          ++isCorrectMember;
        }
      });

      if (isCorrectMember === 2) {
        return true;
      } else {
        return false;
      }
    });

    if (chatRoom) {
      return { roomId: chatRoom.id };
    }

    const myUser = await this.userRepo.findOneBy({ id: myId });
    const partnerUser = await this.userRepo.findOneBy({ id: partnerId });
    if (!myUser || !partnerUser) {
      throw new BadRequestException('존재하지 않는 유저입니다.');
    }

    let chatRoomDataDto: ChatRoomDataDto;
    await this.dataSource.transaction(async (t) => {
      const chatRoomForCreate = new ChatRoom();
      chatRoomForCreate.title = `Dm Room of ${myUser.nickname} and ${partnerUser.nickname}`;
      chatRoomForCreate.ownerId = myId;
      chatRoomForCreate.isDm = true;

      chatRoomDataDto = (await t.save(chatRoomForCreate)).toChatRoomDataDto();

      const chatParticipantForMe = new ChatParticipant();
      chatParticipantForMe.chatRoomId = chatRoomDataDto.roomId;
      chatParticipantForMe.userId = myId;
      chatParticipantForMe.role = 'owner';
      await t.save(chatParticipantForMe);
      const chatParticipantForPartner = new ChatParticipant();
      chatParticipantForPartner.chatRoomId = chatRoomDataDto.roomId;
      chatParticipantForPartner.userId = partnerId;
      await t.save(chatParticipantForPartner);
    });

    this.chatLobbyGateway.emitParticipantingChatRoomList(
      chatRoomDataDto.roomId,
    );
    return { roomId: chatRoomDataDto.roomId };
  }

  async getChatContentsForEmit(
    roomId: number,
    userId: number,
  ): Promise<ChatContentDto[] | string> {
    const participant = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId,
    });

    if (!participant) {
      this.logger.error(
        `getChatContentsForEmit: 참여중인 채팅방이 아닙니다. userId: ${userId}, roomId: ${roomId}`,
      );
      return '참여중인 채팅방이 아닙니다.';
    }

    const { createdTime: participatedTime } = participant;

    const blockedUsers = await this.blockedUserRepo.findBy({
      blockerId: userId,
    });

    const chatContents = await this.chatContentsRepo
      .createQueryBuilder('chatContents')
      .leftJoinAndSelect('chatContents.user', 'user')
      .leftJoinAndSelect('user.chatParticipant', 'chatParticipant')
      .where('chatContents.chatRoomId = :roomId', { roomId })
      .andWhere('chatContents.createdTime > :participatedTime', {
        participatedTime,
      })
      .orderBy('chatContents.createdTime', 'ASC')
      .getMany();

    const result = chatContents
      .filter((chatContent) => {
        if (chatContent.isNotice) {
          return true;
        }

        for (const blockedUser of blockedUsers) {
          if (
            chatContent.userId === blockedUser.blockedId &&
            chatContent.createdTime > blockedUser.createdTime
          ) {
            return false;
          }
        }
        return true;
      })
      .map((chatContent) => {
        return chatContent.toChatContentDto();
      });

    return result;
  }

  async getChatContents(
    user: User,
    roomId: number,
    userId: number,
  ): Promise<ChatContentDto[]> {
    if (user.id !== userId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    const participant = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId,
    });
    if (!participant) {
      throw new BadRequestException('참여중인 채팅방이 아닙니다.');
    }
    const { createdTime: participatedTime } = participant;
    const blockedUsers = await this.blockedUserRepo.findBy({
      blockerId: userId,
    });

    const chatContents = await this.chatContentsRepo
      .createQueryBuilder('chatContents')
      .leftJoinAndSelect('chatContents.user', 'user')
      .leftJoinAndSelect('user.chatParticipant', 'chatParticipant')
      .where('chatContents.chatRoomId = :roomId', { roomId })
      .andWhere('chatContents.createdTime > :participatedTime', {
        participatedTime,
      })
      .orderBy('chatContents.createdTime', 'ASC')
      .getMany();

    const result = chatContents
      .filter((chatContent) => {
        if (chatContent.isNotice) {
          return true;
        }

        for (const blockedUser of blockedUsers) {
          if (
            chatContent.userId === blockedUser.blockedId &&
            chatContent.createdTime > blockedUser.createdTime
          ) {
            return false;
          }
        }
        return true;
      })
      .map((chatContent) => {
        return chatContent.toChatContentDto();
      });

    return result;
  }

  async getChatParticipantProfile(
    user: User,
    roomId: number,
    myId: number,
    targetId: number,
  ): Promise<ChatParticipantProfileDto> {
    if (user.id !== myId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    const myUser = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId: myId,
    });
    const targetUser = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId: targetId,
    });
    if (!myUser || !targetUser) {
      throw new BadRequestException('채팅방에 유저가 존재하지 않습니다.');
    }

    const foundChatParticipant = await this.chatParticipantRepo
      .createQueryBuilder('chatParticipant')
      .leftJoinAndSelect('chatParticipant.user', 'user')
      .leftJoinAndSelect('user.follow', 'follow')
      .leftJoinAndSelect('user.blocked', 'blocked')
      .where('chatParticipant.chatRoomId = :roomId', { roomId })
      .andWhere('chatParticipant.userId = :targetId', { targetId })
      .getOneOrFail();

    return {
      ...foundChatParticipant.user.toUserProfileDto(myId),
      isMuted: foundChatParticipant.isMuted,
      role: foundChatParticipant.role,
    };
  }

  async isMutedUser(roomId: number, userId: number): Promise<boolean> {
    const chatParticipant = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId,
    });

    if (!chatParticipant) {
      throw new BadRequestException(
        `해당하는 채팅방에 참여중인 유저가 아닙니다.`,
      );
    }

    return chatParticipant.isMuted;
  }

  async isBannedUser(roomId: number, userId: number): Promise<boolean> {
    const chatParticipant = await this.chatParticipantRepo.findOneBy({
      chatRoomId: roomId,
      userId,
    });

    if (!chatParticipant) {
      throw new BadRequestException(
        `해당하는 채팅방에 참여중인 유저가 아닙니다.`,
      );
    }

    return chatParticipant.isBanned;
  }

  addMuteTimeout(
    name: string,
    milliseconds: number,
    chatParticipant: ChatParticipant,
  ): void {
    const callback = async () => {
      chatParticipant.isMuted = false;
      chatParticipant.save();
      this.logger.warn(
        `Scheduler ${name}(name) executed. Now ${chatParticipant.id}(chatParticipantId) is unmuted.`,
      );
      this.schedulerRegistry.deleteTimeout(name);
      // 음소거 해제 메세지 db에 저장
      const { id: createdChatContentId } = await this.chatContentsRepo.save({
        chatRoomId: chatParticipant.chatRoomId,
        userId: chatParticipant.userId,
        content: `님의 채팅 금지가 해제되었습니다.`,
        isNotice: true,
      });

      // 채널 유저들에게 음소거해제 메세지 전송
      this.chatGateway.sendNoticeMessage(
        chatParticipant.chatRoomId,
        await this.getChatContentDtoForEmit(createdChatContentId),
      );
    };

    const timeout = setTimeout(callback, milliseconds);
    this.schedulerRegistry.addTimeout(name, timeout);
  }

  deleteMuteTimeout(name: string): void {
    this.schedulerRegistry.deleteTimeout(name);
    this.logger.warn(`Scheduler ${name}(name) deleted!`);
  }

  addBanTimeout(
    name: string,
    milliseconds: number,
    chatParticipant: ChatParticipant,
  ): void {
    const callback = async () => {
      await this.chatParticipantRepo.delete(chatParticipant.id);
      this.logger.warn(
        `Scheduler ${name}(name) executed. Now ${chatParticipant.id}(chatParticipantId) is unbaned.`,
      );
      this.schedulerRegistry.deleteTimeout(name);

      // 강퇴 해제 메세지 db에 저장
      const { id: createdChatContentId } = await this.chatContentsRepo.save({
        chatRoomId: chatParticipant.chatRoomId,
        userId: chatParticipant.userId,
        content: `님의 채팅방 입장 금지가 해제되었습니다.`,
        isNotice: true,
      });

      // 채널 유저들에게 강퇴해제 메세지 전송
      this.chatGateway.sendNoticeMessage(
        chatParticipant.chatRoomId,
        await this.getChatContentDtoForEmit(createdChatContentId),
      );
    };

    const timeout = setTimeout(callback, milliseconds);
    this.schedulerRegistry.addTimeout(name, timeout);
  }

  // deleteBanTimeout(name: string): void {
  //   this.schedulerRegistry.deleteTimeout(name);
  //   this.logger.warn(`Scheduler ${name}(name) deleted!`);
  // }

  async getParticipantingChatRoomsForEmit(
    userId: number,
  ): Promise<ChatRoomDto[]> {
    const chatParticipants = await this.chatParticipantRepo
      .createQueryBuilder('chatParticipant')
      .where('chatParticipant.isBanned = false')
      .andWhere('chatParticipant.userId = :userId', { userId })
      .getMany();

    const participantingChatRoomIds = chatParticipants.map((p) => p.chatRoomId);

    let query = this.chatRoomRepo
      .createQueryBuilder('chatRoom')
      .leftJoinAndSelect('chatRoom.chatParticipant', 'chatParticipant');

    if (participantingChatRoomIds.length) {
      query = query.where('chatRoom.id in (:...chatRoomIds)', {
        chatRoomIds: participantingChatRoomIds,
      });
    }

    const participantingChatRooms = await query.getMany();

    return participantingChatRooms.map((chatRoom) => {
      console.log('\n chat participants cnt', chatRoom.chatParticipant);
      return chatRoom.toChatRoomDto();
    });
  }
}
