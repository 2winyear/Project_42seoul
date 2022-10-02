import { forwardRef, Inject, Logger } from '@nestjs/common';
import {
  ConnectedSocket,
  MessageBody,
  OnGatewayConnection,
  OnGatewayDisconnect,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { User } from 'src/users/entities/users.entity';
import { UserStatusContainer } from 'src/userStatus/userStatus.service';
import { UsersService } from 'src/users/users.service';
import { ChatService } from './chat.service';
import { ChatContentDto } from './dto/chatContents.dto';
import { AuthService } from 'src/auth/auth.service';
import { ChatRoomUserDto } from './dto/chatParticipant.dto';

/**
 * recieveMessage
 * when send chat to client from server
 * nickname, msg, avatar, createdTime, isBroadcast, isMyMessage
 *
 * sendMessage
 * when send chat to server from client
 * userId, roomId, message
 */

// export class ChatToClientDto {
//   userId: number;
//   nickname: string;
//   avatar: string;
//   msg: string;
//   createdTime: Date;
//   isBroadcast: boolean;
//   // isMyMessage: boolean; // 소켓에 유저의 정보를 저장할 수 있나? 없다면 isMyMessage를 구분하여 리턴할 수 없음. 클라이언트에서 받은 데이터의 userId와 클라이언트 자신의 userId를 비교해야 할 듯
// }

class ChatToServerDto {
  userId: number;
  roomId: number;
  message: string;
}

@WebSocketGateway({ namespace: '/ws-chat', cors: { origin: '*' } })
export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect {
  constructor(
    @Inject(forwardRef(() => ChatService))
    private readonly chatService: ChatService,
    @Inject(forwardRef(() => UsersService))
    private readonly userService: UsersService,
    private readonly userStats: UserStatusContainer,
  ) {}

  @WebSocketServer() wss: Server;

  private logger: Logger = new Logger('ChatGateway');

  // Map<roomId, Map<userId, socketId>>
  connectedSocketMap = new Map<string, Map<string, string>>();

  async handleConnection(client: Socket) {
    const roomId = client.handshake.query.roomId as string;
    const userId = client.handshake.query.userId as string;

    try {
      if (!(await this.chatService.isExistMember(+roomId, +userId))) {
        this.wss.to(client.id).emit('disconnectSocket', null);
        client.disconnect();
        return;
      }
    } catch (error) {
      this.wss.to(client.id).emit('disconnectSocket', null);
      client.disconnect();
      return;
    }

    this.logger.log(`socket id: ${client.id}, userId: ${userId} connected`);

    client.join(roomId);
    if (this.connectedSocketMap.has(roomId)) {
      const socketId = this.getParticipatingChatSocketId(
        roomId.toString(),
        userId.toString(),
      );
      this.wss.to(socketId).disconnectSockets();
      this.connectedSocketMap.get(roomId).set(userId, client.id);
    } else {
      const socketUser = new Map<string, string>();
      socketUser.set(userId, client.id);
      this.connectedSocketMap.set(roomId, socketUser);
    }

    this.userStats.setSocket(+userId, client);
    this.emitChatHistoryToParticipatingChatRooms(+userId);
  }

  async handleDisconnect(client: Socket) {
    this.logger.log(`socket id: ${client.id} disconnected`);
    this.connectedSocketMap.forEach((userSocket) => {
      userSocket.forEach((socketId, userId) => {
        if (socketId === client.id) {
          userSocket.delete(userId);
          this.userStats.removeSocket(client);
        }
      });
    });
  }

  // 채팅방에 처음 들어왔을 때 입장 메세지
  // 채팅방에서 나갔을 때 퇴장 메세지
  sendNoticeMessage(roomId: number, chatContentDto: ChatContentDto): void {
    this.logger.log(`roomId: ${roomId}, emit recieveMessage`);
    this.wss.to(roomId.toString()).emit('recieveMessage', chatContentDto);
  }

  // sendChatHistory(roomId: number, chatContentDtos: ChatContentDto[]): void {
  //   this.logger.log(`roomId: ${roomId}, emit recieveChatHistory`);
  //   this.wss.to(roomId.toString()).emit('recieveChatHistory', chatContentDtos);
  // }
  getParticipatingChatSocketId(roomId: string, userId: string) {
    return this.connectedSocketMap.get(roomId).get(userId);
  }

  getParticipatingChatRoomIds(userId: number): string[] {
    const participatingChatRoomIds = [];

    this.connectedSocketMap.forEach((userSocket, roomId) => {
      let isParticipantingRoom = false;

      userSocket.forEach((socketId, userIdInMap) => {
        if (userIdInMap === userId.toString()) {
          isParticipantingRoom = true;
        }
      });

      if (isParticipantingRoom) {
        participatingChatRoomIds.push(roomId);
      }
    });

    return participatingChatRoomIds;
  }

  async updateUserInfoToJoinedChatRooms(
    user: User,
    userId: number,
  ): Promise<void> {
    const joinedChatRoomIds = (
      await this.chatService.getParticipatingChatRooms(user, userId)
    ).map((chatRoom) => chatRoom.roomId);
    joinedChatRoomIds.forEach((chatRoomId) => {
      const userSocket = this.connectedSocketMap.get(chatRoomId.toString());

      if (userSocket) {
        userSocket.forEach(async (socketId, userIdInRoom) => {
          const chatContentDtos = await this.chatService.getChatContentsForEmit(
            chatRoomId,
            +userIdInRoom,
          );

          this.wss.to(socketId).emit('reloadChatHistory', chatContentDtos);
        });
      }

      this.emitChatRoomParticipants(chatRoomId.toString());
    });
  }

  emitChatHistoryToParticipatingChatRooms(
    userIdOfupdatedNickname: number,
  ): void {
    const participantingChatRoomIds = this.getParticipatingChatRoomIds(
      userIdOfupdatedNickname,
    );

    participantingChatRoomIds.forEach((roomId) => {
      this.connectedSocketMap
        .get(roomId.toString())
        .forEach(async (socketId, userIdInRoom) => {
          const chatContentDtos = await this.chatService.getChatContentsForEmit(
            +roomId,
            +userIdInRoom,
          );
          if (chatContentDtos === '참여중인 채팅방이 아닙니다.') {
            console.log('participantingChatRoomIds');
            this.wss.to(socketId).emit('disconnectSocket', chatContentDtos);
          } else
            this.wss.to(socketId).emit('reloadChatHistory', chatContentDtos);
        });
    });
  }

  async emitChatHistoryToSocketThatSpecificUserIsParticipating(
    userId: number,
  ): Promise<void> {
    const participantingChatRoomIds = this.getParticipatingChatRoomIds(userId);

    participantingChatRoomIds.forEach((roomId) => {
      this.connectedSocketMap
        .get(roomId.toString())
        .forEach(async (socketId, userIdInRoom) => {
          const chatContentDtos = await this.chatService.getChatContentsForEmit(
            +roomId,
            +userIdInRoom,
          );
          if (chatContentDtos === '참여중인 채팅방이 아닙니다.') {
            console.log(
              'emitChatHistoryToSocketThatSpecificUserIsParticipating',
            );
            this.wss.to(socketId).emit('disconnectSocket', chatContentDtos);
          } else
            this.wss.to(socketId).emit('reloadChatHistory', chatContentDtos);
        });
    });
  }

  getParticipatingSocketIds(userId: string): string[] {
    const socketIds: string[] = [];

    this.connectedSocketMap.forEach((userSocket) => {
      const socketId = userSocket.get(userId);

      if (socketId) {
        socketIds.push(socketId);
      }
    });

    return socketIds;
  }

  // 방 제목 변경 시 해당 채팅방에 연결된 소켓에 방 제목 emit
  emitChatRoomTitle(roomId: string, title: string): void {
    this.wss.to(roomId).emit('updateChatRoomTitle', title);
  }

  // 유저 상태변화 시 참여중인 채팅방에 유저 목록 emit
  async emitChatRoomParticipants(roomId: string): Promise<ChatRoomUserDto[]> {
    let chatRoomUserDtos: ChatRoomUserDto[];
    try {
      chatRoomUserDtos = await this.chatService.getRoomParticipants(+roomId);
      this.wss.to(roomId).emit('updateChatRoomParticipants', chatRoomUserDtos);
    } catch (error) {
      console.log(error);
    }
    return chatRoomUserDtos;
  }

  // 유저 상태 변화 시 나를 친구추가 한 유저의 친구 목록 emit
  async emitFriendList(myId: number) {
    // 나를 친구 추가한 유저들의 id들을 찾기: followerIds
    const followerIds = await this.userService.getFollowerIds(myId);

    followerIds.forEach(async (followerId) => {
      const socketIds = this.getParticipatingSocketIds(followerId.toString());
      const friendList = await this.userService.getFriendsForEmit(followerId); // 친구 목록 가져오기

      // 있으면 해당 소켓에 친구 목록 emit
      socketIds?.forEach((socketId) => {
        this.wss.to(socketId).emit('updateFriendList', friendList);
      });
    });
  }

  // 채팅방에서 권한 변경 시 emit
  emitRole(roomId: string, userId: string, role: string) {
    const targetSocketId = this.getParticipatingChatSocketId(roomId, userId);

    this.wss.to(targetSocketId).emit('updateRole', role);
  }

  disconnectUser(roomId: number, userId: number) {
    const socketId = this.getParticipatingChatSocketId(
      roomId.toString(),
      userId.toString(),
    );
    console.log('disconnectUser');
    this.wss.to(socketId).emit('disconnectSocket', null);
    this.wss.to(socketId).disconnectSockets();
  }
  /**
   * 채팅 프로세스
   * 채팅 페이지 진입 시 소켓 연결
   * 클라이언트에서 채팅 보내면 서버에서 받고 db에 저장 후 채팅방 참여자에게 메세지 리턴
   * 클라이언트에서 받은 메세지의 userId가 클라이언트의 userId와 같으면 내가보낸 메세지로 출력
   * 클라이언트에서 받은 메세지의 userId가 클라이언트의 userId와 다르면 다른 사용자가 보낸 메세지로 출력
   * 채팅 페이지 이탈 시 소켓 연결 해제
   */
  // 채팅을 보냈을 때 채팅방 참여자에게 메세지 전달
  @SubscribeMessage('refreshChatRoom')
  async reloadChatHistoryForSpecificUser(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { roomId: number; userId: number },
  ): Promise<void> {
    const chatContentDtos = await this.chatService.getChatContentsForEmit(
      data.roomId,
      data.userId,
    );
    if (chatContentDtos instanceof String) {
      console.log('in reload history');
      client.emit('disconnectSocket', chatContentDtos);
    } else client.emit('reloadChatHistory', chatContentDtos);
  }

  @SubscribeMessage('sendMessage')
  async handleMessage(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: ChatToServerDto,
  ): Promise<void> {
    this.logger.log(`roomId: ${data.roomId}, on sendMessage`);

    // 음소거, 강퇴 상태일 경우 얼리 리턴
    if (await this.chatService.isMutedUser(data.roomId, data.userId)) {
      return;
    }
    if (await this.chatService.isBannedUser(data.roomId, data.userId)) {
      return;
    }

    const chatContentDto = await this.chatService.createChatContent(
      data.userId,
      data.roomId,
      data.message,
    );

    const userInSocketRoom = this.connectedSocketMap.get(
      data.roomId.toString(),
    );

    const userIdsForCheck: number[] = [];
    for (const x of userInSocketRoom.keys()) {
      userIdsForCheck.push(+x);
    }

    const unblockedUserIds = await this.userService.getUnblockedUserIds(
      userIdsForCheck,
      data.userId,
    );

    console.log(this.connectedSocketMap);
    userInSocketRoom.forEach((socketId, userId) => {
      if (!unblockedUserIds.includes(+userId)) {
        return;
      }
      this.wss.to(socketId).emit('recieveMessage', chatContentDto);
    });
    // const socketsForEmit = this.wss
    //   .to(data.roomId.toString())
    //   .emit('recieveMessage', chatContentDto);
  }

  // 클라이언트가 받은 채팅을 검증(차단한 유저인지)하기 위해 사용
  // 받은 채팅을 보낸 유저가 내가 차단한 유저이면 true리턴 차단하지 않았으면 false 리턴
  // @SubscribeMessage('isMessageFromBlockedUser')
  // async isMessageFromBlockedUser(
  //   @ConnectedSocket() client: Socket,
  //   @MessageBody() data: { senderId: string; myId: string }, // senderId: 메세지 보낸 유저 id, myId: 메세지 받은 유저 id
  // ): Promise<void> {
  //   this.logger.log(`on isMessageFromBlockedUser`);

  //   const res = await this.chatService.isMessageFromBlockedUser(
  //     +data.myId,
  //     +data.senderId,
  //   );

  //   client.emit('isMessageFromBlockedUserResult', res);
  // }

  // @SubscribeMessage('clientDisconnect')
  // clientDisconnect(
  //   @ConnectedSocket() client: Socket,
  //   @MessageBody() data: { userId: string; roomId: string },
  // ): void {
  //   this.logger.log('on clientDisconnect');
  //   client.disconnect();
  //   if (this.connectedSocketMap.has(data.roomId)) {
  //     this.connectedSocketMap.get(data.roomId).delete(client.id);
  //   }
  // }
}
