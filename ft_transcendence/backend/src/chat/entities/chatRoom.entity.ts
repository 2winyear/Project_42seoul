import { ApiProperty } from '@nestjs/swagger';
import {
  BaseEntity,
  Column,
  Entity,
  OneToMany,
  PrimaryGeneratedColumn,
} from 'typeorm';
import {
  ChatRoomDataDto,
  ChatRoomDto as ChatRoomDto,
} from '../dto/chatRoom.dto';
import { ChatContents } from './chatContents.entity';
import { ChatParticipant } from './chatParticipant.entity';

@Entity()
export class ChatRoom extends BaseEntity {
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty({ description: '채팅방 제목' })
  @Column()
  title: string;

  @ApiProperty({ description: '채팅방 비밀번호' })
  @Column({ nullable: true, default: null })
  password: string | null;

  @ApiProperty({ description: '채팅방 소유자 userId' })
  @Column()
  ownerId: number;

  @ApiProperty({ description: 'dm방인지 여부' })
  @Column({ default: false })
  isDm: boolean;

  @OneToMany(
    () => ChatParticipant,
    (chatParticipant) => chatParticipant.chatRoom,
  )
  chatParticipant: ChatParticipant[];

  @OneToMany(() => ChatContents, (chatContents) => chatContents.chatRoom)
  chatContents: ChatContents[];

  toChatRoomDto(): ChatRoomDto {
    if (this.chatParticipant === undefined) {
      throw Error('chatParticipant join required to chatRoom');
    }

    const chatRoomsDto = new ChatRoomDto();
    chatRoomsDto.roomId = this.id;
    chatRoomsDto.title = this.title;
    chatRoomsDto.isPublic = this.password ? false : true;
    chatRoomsDto.ownerId = this.ownerId;
    chatRoomsDto.numberOfParticipants = this.chatParticipant.filter(
      (person) => !person.isBanned,
    ).length;
    chatRoomsDto.isDm = this.isDm;

    return chatRoomsDto;
  }

  toChatRoomDataDto(): ChatRoomDataDto {
    const chatRoomDataDto = new ChatRoomDataDto();
    chatRoomDataDto.roomId = this.id;
    chatRoomDataDto.title = this.title;
    chatRoomDataDto.ownerId = this.ownerId;
    chatRoomDataDto.isDm = this.isDm;

    return chatRoomDataDto;
  }
}
