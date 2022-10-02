import { forwardRef, Inject, Logger } from '@nestjs/common';
import {
  OnGatewayConnection,
  OnGatewayDisconnect,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { first } from 'rxjs';
import { Server, Socket } from 'socket.io';
import { GameGateway } from 'src/game/game.gateway';
import { SimpleUserDto } from 'src/users/dto/users.dto';
import { UsersService } from 'src/users/users.service';
import { UserStatusContainer } from 'src/userStatus/userStatus.service';
import { FindRelationsNotFoundError } from 'typeorm';
import { ChatService } from './chat.service';
import { ChatRoomUserDto } from './dto/chatParticipant.dto';

@WebSocketGateway({ namespace: '/ws-chatLobby', cors: { origin: '*' } })
export class ChatLobbyGateway
  implements OnGatewayConnection, OnGatewayDisconnect
{
  constructor(
    @Inject(forwardRef(() => ChatService))
    private readonly chatService: ChatService,
    @Inject(forwardRef(() => UsersService))
    private readonly userService: UsersService,
    @Inject(forwardRef(() => UserStatusContainer))
    private readonly userStats: UserStatusContainer,
    private readonly gameGateway: GameGateway,
  ) {}

  @WebSocketServer() wss: Server;

  private logger: Logger = new Logger('LobbyGateway');

  // Map<userId, Set<socketId>>
  connectedSocketMap = new Map<string, Set<string>>();

  handleConnection(client: Socket): void {
    const userId = client.handshake.query.userId as string;

    this.logger.log(
      `socketId: ${client.id}, userId: ${userId} connected at lobby`,
    );

    if (this.connectedSocketMap.has(userId)) {
      this.connectedSocketMap.get(userId).add(client.id);
    } else {
      const set = new Set([client.id]);
      this.connectedSocketMap.set(userId, set);
    }

    this.userStats.setSocket(+userId, client);
    // 최초 목록들은 api 요청으로 처리하는걸로 협의
    // 특정 소켓에 채팅방 목록 emit
    // this.emitChatRoomList(client.id);
    // 특정 소켓에 전체 유저 목록 emit
    // this.emitUserList(client.id);
  }

  handleDisconnect(client: Socket): void {
    this.logger.log(`socket id: ${client.id} disconnected`);

    this.connectedSocketMap.forEach((set, userId) => {
      set.delete(client.id);
      this.userStats.removeSocket(client);
    });
  }

  // 유저 로그아웃 시 연결된 모든 소켓 disconnect
  disconnectUser(userId: string): void {
    const socketIds = this.connectedSocketMap.get(userId);

    socketIds.forEach((socketId) => {
      this.wss.to(socketId).emit('disconnectSocket', null);
      this.wss.to(socketId).disconnectSockets();
    });

    this.connectedSocketMap.delete(userId);
  }

  // 채팅방 목록 emit
  // 특정 소켓에 emit 할 경우 socketId 매개변수로 전달
  // 로비에 연결된 모든 소켓에 emit할 경우 매개변수 없이 호출
  async emitChatRoomList(socketId?: string): Promise<void> {
    const chatRoomList = await this.chatService.getChatRooms();

    if (socketId) {
      this.wss.to(socketId).emit('updateChatRoomList', chatRoomList);
    } else {
      this.wss.emit('updateChatRoomList', chatRoomList);
    }
  }

  // 로비에 연결된 유저의 id 가져오기
  // getConnectedUserIds(): string[] {
  //   const connectedUserIds: string[] = [];

  //   this.connectedSocketMap.forEach((socketSet, userId) => {
  //     connectedUserIds.push(userId);
  //   });

  //   return connectedUserIds;
  // }

  // 로비에 연결된 특정 유저의 socketId 가져오기
  getConnectedSocketIdsOfUser(userId: string): string[] | undefined {
    const socketIds = this.connectedSocketMap.get(userId);
    if (socketIds) {
      return [...socketIds];
    }
    return undefined;
  }

  // 참여중인 채팅방 목록 emit
  // roomId 인자가 있으면 해당 방 참여자에게만 참여중인 채팅방 목록 emit, 없으면 모두에게 참여중인 채팅방 목록 emit
  // 1. 방 정보가 변경되면 chatLobby의 emitParticipantingChatRoomList 호출: 방 제목 변경, 방 입퇴장(인원수 변경), 방 삭제되는 경우
  async emitParticipantingChatRoomList(roomId?: number): Promise<void> {
    if (!roomId) {
      this.connectedSocketMap.forEach(async (socketSet, userId) => {
        const chatRoomList =
          await this.chatService.getParticipantingChatRoomsForEmit(+userId);
        console.log('\nchatRoomList ', chatRoomList);

        socketSet.forEach((socketId) => {
          this.wss
            .to(socketId)
            .emit('updateParticipnatingChatRoomList', chatRoomList);
        });
      });

      return;
    }

    // 2. 방에 참여중인 유저 id 가져오기 - in chatService
    const chatRoomUserDtos: ChatRoomUserDto[] = [];

    try {
      chatRoomUserDtos.push(
        ...(await this.chatService.getRoomParticipants(roomId)),
      );
    } catch (error) {}

    const participantIds = chatRoomUserDtos.map(
      (chatRoomUserDto) => chatRoomUserDto.userId,
    );

    participantIds.forEach((participantId) => {
      // 3. 2에서 가져온 유저의 id를 현재 로비 소켓에 연결되어 있는 유저의 id로 필터링 - chatLobby의 getConnectedSocketIdsOfUser 함수 활용
      const socketIds = this.getConnectedSocketIdsOfUser(
        participantId.toString(),
      );

      console.log('\n participantIds ', participantIds);
      // 4. 해당 유저의 소켓에 채팅방 목록 emit
      if (socketIds) {
        socketIds.forEach(async (socketId) => {
          const chatRoomList =
            await this.chatService.getParticipantingChatRoomsForEmit(
              participantId,
            );
          console.log('\n chatRoomList ', chatRoomList);

          this.wss
            .to(socketId)
            .emit('updateParticipnatingChatRoomList', chatRoomList);
        });
      }
    });
  }

  // 전체 유저 목록 emit
  // 회원가입, 로그인, 로그아웃, 닉네임 변경 todo: 게입 방 입퇴장(유저 상태 play)
  async emitUserList(socketId?: string): Promise<SimpleUserDto[]> {
    let userList = await this.userService.getUsers();

    userList = userList.filter((user) => user.nickname);
    if (socketId) {
      this.wss.to(socketId).emit('updateUserList', userList);
    } else {
      this.wss.emit('updateUserList', userList);
    }
    return userList;
  }

  // 친구 목록 emit
  // 로그인, 로그아웃, 닉네임 변경 todo: 게입 방 입퇴장(유저 상태 play)
  async emitFriendList(myId: number): Promise<number[]> {
    // 1. 나를 친구추가한 유저 id 가져오기
    const followerIds = await this.userService.getFollowerIds(myId);

    followerIds.forEach(async (followerId) => {
      // 2. 1에서 가져온 유저 id에 연결된 소켓 id 가져오기
      const socketIds = this.getConnectedSocketIdsOfUser(followerId.toString());
      const friendList = await this.userService.getFriendsForEmit(followerId);

      // 3. 1에서 가져온 유저 id의 친구 목록 가져와서 emit
      socketIds?.forEach(async (socketId) => {
        this.wss.to(socketId).emit('updateFriendList', friendList);
      });

      this.gameGateway.broadcastToSelectedLobby(
        followerId,
        'updateFriendList',
        friendList,
      );
    });
    return followerIds;
  }
}
