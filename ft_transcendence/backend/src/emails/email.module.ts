import { MailerService } from '@nestjs-modules/mailer';
import { Module } from '@nestjs/common';
import { UsersModule } from 'src/users/users.module';
import { UsersService } from 'src/users/users.service';
import { EmailService } from './email.service';

@Module({
  // imports: [UsersModule],
  providers: [EmailService],
  exports: [EmailService],
})
export class EmailModule {}
