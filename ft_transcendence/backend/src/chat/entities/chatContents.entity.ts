import { ApiProperty } from '@nestjs/swagger';
import { User } from '../../users/entities/users.entity';
import {
  BaseEntity,
  Column,
  CreateDateColumn,
  Entity,
  ManyToOne,
  PrimaryGeneratedColumn,
} from 'typeorm';
import { ChatContentDto, FromWhomDto } from '../dto/chatContents.dto';
import { ChatRoom } from './chatRoom.entity';
import { ChatParticipant } from './chatParticipant.entity';

@Entity()
export class ChatContents extends BaseEntity {
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty({ description: '[FK] 채팅방 id' })
  @Column()
  chatRoomId: number;

  @ApiProperty({ description: '[FK] 메세지 보낸 유저 id' })
  @Column({ nullable: true })
  userId: number | null;

  @ApiProperty({ description: '메세지 내용' })
  @Column()
  content: string;

  @ApiProperty({ description: '공지 메세지 여부' })
  @Column({ default: false })
  isNotice: boolean;

  @ApiProperty({ description: '메세지 보낸 시간' })
  @CreateDateColumn({ type: 'timestamptz', default: () => 'CURRENT_TIMESTAMP' })
  createdTime: Date;

  @ManyToOne(() => ChatRoom, (chatRoom) => chatRoom.chatContents, {
    onDelete: 'CASCADE',
  })
  chatRoom: ChatRoom;

  @ManyToOne(() => User, (user) => user.sender)
  user: User;

  toChatContentDto(): ChatContentDto {
    const chatContentDto = new ChatContentDto();

    chatContentDto.isBroadcast = this.isNotice;
    chatContentDto.userId = this.userId;
    chatContentDto.nickname = this.user.nickname;
    chatContentDto.avatar = this.user.avatar;
    if (this.isNotice) {
      chatContentDto.message = `${chatContentDto.nickname} ${this.content}`;
    } else {
      chatContentDto.message = this.content;
    }
    chatContentDto.createdTime = this.createdTime.toISOString();

    return chatContentDto;
  }
}
