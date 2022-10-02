import { ApiProperty } from '@nestjs/swagger';
import { IsNumber } from 'class-validator';

export class FollowIdDto {
  @ApiProperty({ description: '팔로우 당하는 사람의 유저 id' })
  @IsNumber()
  followId: number;
}
