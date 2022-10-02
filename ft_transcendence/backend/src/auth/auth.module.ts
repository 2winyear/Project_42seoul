import { forwardRef, Module } from '@nestjs/common';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { TypeOrmModule } from '@nestjs/typeorm';
import { ChatModule } from 'src/chat/chat.module';
import { EmailModule } from 'src/emails/email.module';
import { GameModule } from 'src/game/game.module';
import { User } from 'src/users/entities/users.entity';
import { UsersModule } from 'src/users/users.module';
import { AuthController } from './auth.controller';
import { AuthService } from './auth.service';
import { JwtStrategy } from './jwt.strategy';

@Module({
  imports: [
    TypeOrmModule.forFeature([User]),
    PassportModule.register({ defaultStrategy: 'jwt' }),
    JwtModule.register({
      secret: process.env.EC2_JWT_SECRET || process.env.JWT_SECRET,
      signOptions: {
        expiresIn: process.env.EC2_JWT_EXPIRESIN || process.env.JWT_EXPIRESIN,
      },
    }),
    forwardRef(() => UsersModule),
    EmailModule,
    forwardRef(() => ChatModule),
    forwardRef(() => GameModule),
  ],
  controllers: [AuthController],
  providers: [AuthService, JwtStrategy],
  exports: [JwtStrategy, PassportModule, AuthService],
})
export class AuthModule {}
