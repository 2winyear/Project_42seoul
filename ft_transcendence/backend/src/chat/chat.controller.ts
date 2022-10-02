import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  ParseIntPipe,
  Post,
  Put,
  Query,
  UseGuards,
} from '@nestjs/common';
import { ApiBearerAuth, ApiOperation, ApiTags } from '@nestjs/swagger';
import { ChatService } from './chat.service';
import {
  ChatRoomDataDto,
  SetChatRoomDto,
  RoomPasswordDto,
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
import { AuthGuard } from '@nestjs/passport';
import { User } from 'src/users/entities/users.entity';
import { GetJwtUser } from 'src/auth/jwt.strategy';

@ApiTags('chats')
@ApiBearerAuth('access-token')
@Controller('chats')
@UseGuards(AuthGuard())
export class ChatController {
  constructor(private readonly chatService: ChatService) {}

  @ApiOperation({ summary: 'kankim✅ 채팅방 목록 가져오기' })
  @Get('')
  async getChatRooms(): Promise<ChatRoomDto[]> {
    const chatRooms = await this.chatService.getChatRooms();

    return chatRooms;
  }

  @ApiOperation({ summary: 'jihokim✅ 채팅방 정보' })
  @Get('/:roomId')
  async getChatRoomData(
    @Param('roomId', ParseIntPipe) roomId: number,
  ): Promise<ChatRoomDataDto> {
    const chatRoomData = await this.chatService.getChatRoomData(roomId);

    return chatRoomData;
  }

  @ApiOperation({ summary: 'kankim✅ 참여중인 채팅방 목록 가져오기' })
  @Get('/users/:userId')
  async getParticipatingChatRooms(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<ChatRoomDto[]> {
    const chatRooms = this.chatService.getParticipatingChatRooms(user, userId);

    return chatRooms;
  }

  @ApiOperation({ summary: 'kankim✅ 채팅방 만들기' })
  @Post(':userId')
  async createChatRoom(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) userId: number,
    @Body() createChatRoomDto: SetChatRoomDto,
  ): Promise<ChatRoomDataDto> {
    const chatRoom = await this.chatService.createChatRoom(
      user,
      userId,
      createChatRoomDto,
    );

    return chatRoom;
  }

  @ApiOperation({ summary: 'kankim✅ 채팅방 참여자 목록 가져오기' })
  @Get('/:roomId/participants')
  async getChatParticipants(
    @Param('roomId', ParseIntPipe) roomId: number,
  ): Promise<ChatRoomUserDto[]> {
    return await this.chatService.getRoomParticipants(roomId);
  }

  @ApiOperation({ summary: 'kankim✅ 채팅방 입장하기' })
  @Post(':roomId/users/:userId')
  async enterChatRoom(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('userId', ParseIntPipe) userId: number,
    @Body() roomPasswordDto: RoomPasswordDto,
  ): Promise<ChatRoomIdDto> {
    return await this.chatService.enterChatRoom(
      user,
      roomId,
      userId,
      roomPasswordDto.password,
    );
  }

  @ApiOperation({ summary: 'kankim✅ 채팅방 설정' })
  @Put(':roomId/users/:ownerId')
  async updateRoom(
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('ownerId', ParseIntPipe) ownerId: number,
    @Body() updateChatRoomDto: SetChatRoomDto,
  ): Promise<ChatRoomDataDto> {
    return await this.chatService.updateRoom(
      roomId,
      ownerId,
      updateChatRoomDto,
    );
  }

  @ApiOperation({ summary: 'kankim✅ 채팅방 나가기' })
  @Delete(':roomId/users/:userId')
  async exitRoom(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<void> {
    await this.chatService.exitRoom(user, roomId, userId);
  }

  @ApiOperation({ summary: 'kankim✅ dm방 입장하기' })
  @Post(':myId/dmRooms')
  async enterDmRoom(
    @GetJwtUser() user: User,
    @Param('myId', ParseIntPipe) myId: number,
    @Query('partnerId', ParseIntPipe) partnerId: number,
  ): Promise<ChatRoomIdDto> {
    return await this.chatService.enterDmRoom(user, myId, partnerId);
  }

  @ApiOperation({
    summary:
      'kankim *채팅 입력 api 구현 후 테스트 필요* 채팅방 메세지 기록 조회(내가 참여한 시점 이후)',
  })
  @Get(':roomId/chatContents/:userId')
  async getChatContents(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<ChatContentDto[]> {
    return await this.chatService.getChatContents(user, roomId, userId);
  }

  @ApiOperation({ summary: '✅ 관리자로 설정 토글: jihokim' })
  @Put(':roomId/roleToggle')
  async toggleManager(
    @Param('roomId', ParseIntPipe) roomId: number,
    @Query('callingUserId', ParseIntPipe) callingUserId: number,
    @Query('targetUserId', ParseIntPipe) targetUserId: number,
  ): Promise<ParticipantRoleDto> {
    return this.chatService.toggleParticipantRole(
      roomId,
      callingUserId,
      targetUserId,
    );
  }

  @ApiOperation({ summary: 'seungyel✅ ban 시키기' })
  @Put(':roomId/ban/:userId')
  async banParticipant(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('userId', ParseIntPipe) userId: number,
    @Query('targetUserId', ParseIntPipe) targetUserId: number,
  ): Promise<void> {
    return this.chatService.banUser(user, roomId, userId, targetUserId);
  }

  @ApiOperation({ summary: 'kankim✅ kick 시키기' })
  @Put(':roomId/kick/:userId')
  async kickParticipant(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('userId', ParseIntPipe) userId: number,
    @Query('targetUserId', ParseIntPipe) targetUserId: number,
  ): Promise<void> {
    console.log('\n ### 1');
    await this.chatService.kickUser(user, roomId, userId, targetUserId);
  }

  @ApiOperation({ summary: '✅ 음소거 시키기 토글: jihokim' })
  @Put(':roomId/users/:callingUserId/muteToggle')
  async muteParticipant(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('callingUserId', ParseIntPipe) callingUserId: number,
    @Query('targetUserId', ParseIntPipe) targetUserId: number,
  ): Promise<IsMutedDto> {
    return await this.chatService.muteCertainParticipant(
      user,
      roomId,
      callingUserId,
      targetUserId,
    );
  }

  // 인터페이스를 통해 게임 할 수 있도록 초대
  // 인터페이스를 통해 다른 유저의 프로필 보기

  @ApiOperation({ summary: '채팅 등록' })
  @Post(':roomId/users/:userId/messages')
  async submitChatContent(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('userId', ParseIntPipe) userId: number,
    @Body() messageDto: MessageDto,
  ): Promise<void> {
    await this.chatService.submitChatContent(user, roomId, userId, messageDto);
  }

  @ApiOperation({ summary: 'kankim✅ 채팅방에 있는 유저의 프로필 조회' })
  @Get(':roomId/participants/:myId')
  @UseGuards(AuthGuard())
  async getChatParticipantProfile(
    @GetJwtUser() user: User,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Param('myId', ParseIntPipe) myId: number,
    @Query('targetId', ParseIntPipe) targetId: number,
  ): Promise<ChatParticipantProfileDto> {
    return await this.chatService.getChatParticipantProfile(
      user,
      roomId,
      myId,
      targetId,
    );
  }
}
