import { forwardRef, Module } from '@nestjs/common';
import { AuthModule } from 'src/auth/auth.module';
import { ChatModule } from 'src/chat/chat.module';
import { UserStatusContainer } from './userStatus.service';

@Module({
  imports: [forwardRef(() => AuthModule), forwardRef(() => ChatModule)],
  providers: [UserStatusContainer],
  exports: [UserStatusContainer],
})
export class UserStatusModule {}
