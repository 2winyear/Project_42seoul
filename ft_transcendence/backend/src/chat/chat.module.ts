import { forwardRef, Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AuthModule } from 'src/auth/auth.module';
import { GameGateway } from 'src/game/game.gateway';
import { GameModule } from 'src/game/game.module';
import { BlockedUser } from 'src/users/entities/blockedUser.entity';
import { User } from 'src/users/entities/users.entity';
import { UsersModule } from 'src/users/users.module';
import { UserStatusModule } from 'src/userStatus/userStatus.module';
import { ChatController } from './chat.controller';
import { ChatGateway } from './chat.gateway';
import { ChatService } from './chat.service';
import { ChatLobbyGateway } from './chatLobby.gateway';
import { ChatContents } from './entities/chatContents.entity';
import { ChatParticipant } from './entities/chatParticipant.entity';
import { ChatRoom } from './entities/chatRoom.entity';

@Module({
  exports: [ChatGateway, ChatService, ChatLobbyGateway],
  imports: [
    TypeOrmModule.forFeature([
      ChatContents,
      ChatParticipant,
      ChatRoom,
      User,
      BlockedUser,
    ]),
    forwardRef(() => AuthModule),
    forwardRef(() => UsersModule),
    forwardRef(() => UserStatusModule),
    forwardRef(() => GameModule),
  ],
  controllers: [ChatController],
  providers: [ChatService, ChatGateway, ChatLobbyGateway],
})
export class ChatModule {}
