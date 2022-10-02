import { ApiProperty } from '@nestjs/swagger';
import {
  IsBoolean,
  IsEmail,
  IsOptional,
  IsString,
  IsNumber,
} from 'class-validator';

export class IsSignedUpDto {
  @ApiProperty({ description: 'id( DB키 )' })
  @IsNumber()
  userId: number;

  @ApiProperty({ description: '닉네임' })
  @IsString()
  @IsOptional()
  nickname: string | null;

  @ApiProperty({ description: '이메일' })
  @IsEmail()
  email: string;

  @ApiProperty({ description: '유저 데이터' })
  @IsString()
  @IsOptional()
  avatar: string | null;

  @ApiProperty({ description: '2차 인증 여부 ' })
  @IsBoolean()
  isSecondAuthOn: boolean;

  @ApiProperty({ description: 'jwt' })
  @IsString()
  jwt: string;
}

export class CodeStringDto {
  @ApiProperty({ description: '문자열 코드' })
  @IsString()
  code: string;
}

export class IsDuplicateDto {
  @ApiProperty({ description: '닉네임 중복 여부' })
  isDuplicate: boolean;
}

export class SecondAuthResultDto {
  @ApiProperty({ description: '정상 작동하면 true, 아니면 false' })
  isOk: boolean;

  @ApiProperty({ description: '정상일 때 jwt, 실패일 때 null' })
  jwt: string;
}
