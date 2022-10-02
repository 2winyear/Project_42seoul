import { ApiProperty } from '@nestjs/swagger';
import { User } from 'src/users/entities/users.entity';
import {
  BaseEntity,
  Column,
  CreateDateColumn,
  Entity,
  ManyToOne,
  OneToMany,
  PrimaryGeneratedColumn,
} from 'typeorm';
import { ChatContents } from './chatContents.entity';
import { ChatRoom } from './chatRoom.entity';

@Entity()
export class ChatParticipant extends BaseEntity {
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty({ description: '[FK] 채팅방 id' })
  @Column()
  chatRoomId: number;

  @ApiProperty({ description: '[FK] 채팅방 참여자의 유저 id' })
  @Column()
  userId: number;

  @ApiProperty({
    description: "채팅방에서 유저의 역할 ['owner' | 'manager' | 'guest']",
  })
  @Column({ default: 'guest' })
  role: 'owner' | 'manager' | 'guest';

  @ApiProperty({ description: '강퇴 여부' })
  @Column({ default: false })
  isBanned: boolean;

  @ApiProperty({ description: '음소거 여부' })
  @Column({ default: false })
  isMuted: boolean;

  @ApiProperty({ description: '채팅방 입장 시간' })
  @CreateDateColumn({ type: 'timestamptz', default: () => 'CURRENT_TIMESTAMP' })
  createdTime: Date;

  @ManyToOne(() => ChatRoom, (chatRoom) => chatRoom.chatParticipant, {
    onDelete: 'CASCADE',
  })
  chatRoom: ChatRoom;

  @ManyToOne(() => User, (user) => user.chatParticipant)
  user: User;
}
