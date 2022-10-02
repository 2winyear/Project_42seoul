import { ApiProperty } from '@nestjs/swagger';
import {
  BaseEntity,
  Column,
  CreateDateColumn,
  Entity,
  ManyToOne,
  PrimaryGeneratedColumn,
} from 'typeorm';
import { User } from './users.entity';

@Entity()
export class BlockedUser extends BaseEntity {
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty({ description: '[FK] 차단 하는 유저의 id' })
  @Column()
  blockerId: number;

  @ApiProperty({ description: '[FK] 차단 당하는 유저의 id' })
  @Column()
  blockedId: number;

  @ApiProperty({ description: '차단한 시간' })
  @CreateDateColumn({ type: 'timestamptz', default: () => 'CURRENT_TIMESTAMP' })
  createdTime: Date;

  @ManyToOne(() => User, (user) => user.blocker)
  blocker: User;

  @ManyToOne(() => User, (user) => user.blocked)
  blocked: User;
}
