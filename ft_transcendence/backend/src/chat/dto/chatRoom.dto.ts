import { ApiProperty, PickType } from '@nestjs/swagger';
import { IsBoolean, IsOptional, IsString } from 'class-validator';

class ChatRoomBaseDto {
  @ApiProperty({ description: '채팅방 id' })
  roomId: number;

  @ApiProperty({ description: '채팅방 제목' })
  title: string;

  @ApiProperty({ description: '공개방 여부, (공개방: true, 비공개: false)' })
  isPublic: boolean;

  @ApiProperty({ description: '채팅방 소유자' })
  ownerId: number;

  @ApiProperty({ description: '채팅방 참여인원' })
  numberOfParticipants: number;

  @ApiProperty({ description: 'dm방 여부' })
  @IsOptional()
  isDm: boolean;

  @ApiProperty({ description: '채팅방 비밀번호' })
  @IsString()
  @IsOptional()
  password: string | null;
}

export class ChatRoomDto extends PickType(ChatRoomBaseDto, [
  'roomId',
  'title',
  'isPublic',
  'ownerId',
  'numberOfParticipants',
  'isDm',
]) {}

export class ChatRoomDataDto extends PickType(ChatRoomBaseDto, [
  'roomId',
  'title',
  'ownerId',
  'isDm',
]) {}

export class SetChatRoomDto extends PickType(ChatRoomBaseDto, [
  'title',
  'password',
]) {}

export class RoomPasswordDto extends PickType(ChatRoomBaseDto, ['password']) {}

export class ChatRoomIdDto extends PickType(ChatRoomBaseDto, ['roomId']) {}

export class BooleanDto {
  @ApiProperty({ description: 'true or false' })
  @IsBoolean()
  boolean: boolean;
}
