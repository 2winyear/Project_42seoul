import { ApiProperty } from '@nestjs/swagger';
import {
  BaseEntity,
  Column,
  Entity,
  ManyToOne,
  PrimaryGeneratedColumn,
} from 'typeorm';
import { User } from './users.entity';

@Entity()
export class Follow extends BaseEntity {
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty({ description: '[FK] 팔로우 하는 유저의 id' })
  @Column()
  followerId: number;

  @ApiProperty({ description: '[FK] 팔로우 당하는 유저의 id' })
  @Column()
  followId: number;

  @ManyToOne(() => User, (user) => user.follower)
  follower: User;

  @ManyToOne(() => User, (user) => user.follow)
  follow: User;
}
