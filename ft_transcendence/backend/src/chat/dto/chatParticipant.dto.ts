import { ApiProperty, PickType } from '@nestjs/swagger';
import { UserProfileDto } from 'src/users/dto/users.dto';

export class ChatParticipantProfileDto extends UserProfileDto {
  @ApiProperty({ description: '뮤트 여부' })
  isMuted: boolean;

  @ApiProperty({ description: '채팅 참여자 역할' })
  role: 'owner' | 'manager' | 'guest';
}

export class ChatRoomUserDto extends PickType(ChatParticipantProfileDto, [
  'userId',
  'nickname',
  'role',
]) {
  @ApiProperty({ description: '로그인 상태' })
  status: 'on' | 'off' | 'play';
}

export class ParticipantRoleDto extends PickType(ChatParticipantProfileDto, [
  'role',
]) {}

export class IsMutedDto extends PickType(ChatParticipantProfileDto, [
  'isMuted',
]) {}
