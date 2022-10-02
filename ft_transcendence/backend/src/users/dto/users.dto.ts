import { ApiProperty, PickType } from '@nestjs/swagger';
import {
  IsBoolean,
  IsEmail,
  IsNumber,
  IsString,
  MaxLength,
  MinLength,
} from 'class-validator';

export class UserProfileDto {
  @ApiProperty({ description: '유저 id' })
  @IsNumber()
  userId: number;

  @ApiProperty({ description: '유저 닉네임' })
  @IsString()
  @MinLength(2, { message: '닉네임은 최소 2글자로 입력해 주세요.' })
  @MaxLength(8, { message: '닉네임은 최대 8글자로 입력해 주세요.' })
  nickname: string;

  @ApiProperty({ description: '유저 아바타' })
  @IsString()
  avatar: string | null;

  @ApiProperty({ description: '유저 이메일' })
  @IsEmail()
  email: string;

  @ApiProperty({ description: '일반게임 승리 카운트' })
  @IsNumber()
  winCount: number;

  @ApiProperty({ description: '일반게임 패배 카운트' })
  @IsNumber()
  loseCount: number;

  @ApiProperty({ description: '래더게임 승리 카운트' })
  @IsNumber()
  ladderWinCount: number;

  @ApiProperty({ description: '래임게임 패배 카운트' })
  @IsNumber()
  ladderLoseCount: number;

  @ApiProperty({ description: '유저 래더 레벨' })
  @IsNumber()
  ladderLevel: number;

  @ApiProperty({ description: '2차 이메일 인증 활성화 여부' })
  @IsBoolean()
  isSecondAuthOn?: boolean;

  @ApiProperty({ description: '친구인지 여부' })
  @IsBoolean()
  isFriend?: boolean;

  @ApiProperty({ description: '차단한 유저인지 여부' })
  @IsBoolean()
  isBlocked?: boolean;
}

export class TargetIdDto {
  @ApiProperty({ description: '타겟 유저의 id' })
  @IsNumber()
  targetId: number;
}

export class NicknameDto extends PickType(UserProfileDto, ['nickname']) {}

export class EmailDto extends PickType(UserProfileDto, ['email']) {}

export class SimpleUserDto extends PickType(UserProfileDto, [
  'userId',
  'nickname',
]) {
  @ApiProperty({ description: '로그인 상태' })
  status: 'on' | 'off' | 'play';
}

export class GamerInfoDto extends PickType(UserProfileDto, [
  'nickname',
  'avatar',
  'winCount',
  'loseCount',
  'ladderWinCount',
  'ladderLoseCount',
]) {
  @ApiProperty({ description: '레더게임 레벨' })
  @IsNumber()
  ladderLevel: number;
}

export class UpdateUserDto extends PickType(UserProfileDto, [
  'userId',
  'avatar',
  'nickname',
]) {}

export class WinLoseCountDto extends PickType(UserProfileDto, [
  'userId',
  'winCount',
  'loseCount',
  'ladderWinCount',
  'ladderLoseCount',
  'ladderLevel',
]) {}

export class NumberDto {
  @ApiProperty({ description: '숫자' })
  @IsNumber()
  number: number;
}

export class GameRecordDto {
  @ApiProperty({ description: '래더게임 여부' })
  isLadder: boolean;

  @ApiProperty({ description: '승리 여부' })
  isWin: boolean;

  @ApiProperty({ description: '상대 닉네임' })
  opponentNickname: string;
}
