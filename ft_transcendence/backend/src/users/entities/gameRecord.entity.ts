import { ApiProperty } from '@nestjs/swagger';
import { User } from 'src/users/entities/users.entity';
import {
  BaseEntity,
  Column,
  Entity,
  ManyToOne,
  PrimaryGeneratedColumn,
} from 'typeorm';
import { GameRecordDto } from '../dto/users.dto';

@Entity()
export class GameRecord extends BaseEntity {
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty({ description: '[FK] 첫번째 플레이어의 유저 id' })
  @Column()
  playerOneId: number;

  @ApiProperty({ description: '[FK] 두번째 플레이어의 유저 id' })
  @Column()
  playerTwoId: number;

  @ApiProperty({ description: '첫번째 플레이어의 점수' })
  @Column()
  playerOneScore: number;

  @ApiProperty({ description: '두번째 플레이어의 점수' })
  @Column()
  playerTwoScore: number;

  @ApiProperty({ description: '승자 id' })
  @Column()
  winnerId: number;

  @ApiProperty({ description: '래더게임 여부' })
  @Column({ default: false })
  isLadder: boolean;

  @ManyToOne(() => User, (user) => user.playerOne)
  playerOne: User;

  @ManyToOne(() => User, (user) => user.playerTwo)
  playerTwo: User;

  toGameRecordDto(myId: number): GameRecordDto {
    const gameRecordDto = new GameRecordDto();

    gameRecordDto.isLadder = this.isLadder;
    gameRecordDto.isWin = this.winnerId === myId ? true : false;
    gameRecordDto.opponentNickname =
      this.playerOneId === myId
        ? this.playerTwo.nickname
        : this.playerOne.nickname;

    return gameRecordDto;
  }
}
