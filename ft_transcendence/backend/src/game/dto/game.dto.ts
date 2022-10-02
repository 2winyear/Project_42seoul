import { ApiProperty, PickType } from '@nestjs/swagger';
import {
  IsBoolean,
  IsNumber,
  IsString,
  IsOptional,
  IsNotEmpty,
} from 'class-validator';

export class GameRoomProfileDto {
  @ApiProperty({ description: '게임방 id' })
  @IsNumber()
  gameId: number;

  @ApiProperty({ description: '게임방 오너 유저 id' })
  @IsNumber()
  ownerId: number;

  @ApiProperty({ description: '게임방 제목' })
  @IsString()
  roomTitle: string;

  @ApiProperty({ description: '게임 모드' })
  @IsString()
  gameMode: 'normal' | 'speed' | 'obstacle';

  @ApiProperty({ description: '게임방 인원수' })
  @IsNumber()
  playerCount: number;

  @ApiProperty({ description: '게임방 공개방인지 여부' })
  @IsBoolean()
  isPublic: boolean;

  @ApiProperty({ description: '게임방이 게임중인지 여부' })
  @IsBoolean()
  isStart: boolean;
}

export class CreateGameRoomDto extends PickType(GameRoomProfileDto, [
  'ownerId',
  'roomTitle',
  'gameMode',
]) {
  @ApiProperty({ description: '게임방 비밀번호' })
  @IsString()
  @IsNotEmpty()
  @IsOptional()
  password: string | null;
}
export class SimpleGameRoomDto extends PickType(GameRoomProfileDto, [
  'gameId',
  'gameMode',
  'ownerId',
  'roomTitle',
]) {}

export class GameRoomPasswordDto extends PickType(CreateGameRoomDto, [
  'password',
]) {}

export class GameRoomIdDto extends PickType(GameRoomProfileDto, ['gameId']) {}

export class GameResultDto {
  @ApiProperty({ description: '래더게임 여부' })
  isLadder: boolean;

  @ApiProperty({ description: '[FK] 첫번째 플레이어의 유저 id' })
  playerOneId: number;

  @ApiProperty({ description: '[FK] 두번째 플레이어의 유저 id' })
  playerTwoId: number;

  @ApiProperty({ description: '첫번째 플레이어의 점수' })
  playerOneScore: number;

  @ApiProperty({ description: '두번째 플레이어의 점수' })
  playerTwoScore: number;

  @ApiProperty({ description: '승자 id' })
  winnerId: number;
}

export class ChallengeResponseDto {
  @ApiProperty({ description: '대전 가능 여부' })
  available: boolean;

  @ApiProperty({ description: '대전 가능 여부' })
  blocked: boolean;

  @ApiProperty({ description: '상대 로그인 상태' })
  status: 'on' | 'off' | 'play';
}
