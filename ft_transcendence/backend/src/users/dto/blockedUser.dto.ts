import { ApiProperty } from '@nestjs/swagger';
import { IsBoolean } from 'class-validator';

export class BlockResultDto {
  @ApiProperty({
    description: '유저가 차단되었으면 true, 차단 해제되었으면 false',
  })
  @IsBoolean()
  isBlocked: boolean;
}
