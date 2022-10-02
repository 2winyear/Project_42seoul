import { ApiProperty, PickType } from '@nestjs/swagger';
import {
  IsBoolean,
  IsOptional,
  IsString,
  IsDateString,
  ValidateNested,
  IsNumber,
} from 'class-validator';
import { extend } from 'dayjs';
import { UserProfileDto } from 'src/users/dto/users.dto';
import { ChatRoomUserDto } from './chatParticipant.dto';

export class FromWhomDto extends PickType(ChatRoomUserDto, ['nickname']) {
  @ApiProperty({ description: '유저 프로필 사진' })
  avatar: string | null;
}

export class ChatContentDto extends PickType(UserProfileDto, [
  'userId',
  'nickname',
  'avatar',
]) {
  @ApiProperty({ description: '공지 메시지인지 여부' })
  @IsBoolean()
  isBroadcast: boolean;

  @ApiProperty({ description: '채팅 내용' })
  @IsString()
  message: string;

  @ApiProperty({
    description:
      '만들어진 시간, 요청 시 보낼 필요 없음, 리스폰스로 줄 때만 넘어갈 예정',
  })
  @IsDateString()
  createdTime: string;
}

export class CreateChatContentDto extends PickType(ChatContentDto, [
  'isBroadcast',
  'message',
]) {}

export class MessageDto extends PickType(ChatContentDto, ['message']) {}
