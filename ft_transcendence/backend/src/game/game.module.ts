import { forwardRef, Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from '../users/entities/users.entity';
import { GameController } from './game.controller';
import { GameService } from './game.service';
import { GameGateway } from './game.gateway';
import { PassportModule } from '@nestjs/passport';
import { AuthModule } from 'src/auth/auth.module';
import { GameEnv } from './class/game.class.GameEnv';
import { UserStatusModule } from 'src/userStatus/userStatus.module';
import { UsersModule } from 'src/users/users.module';

@Module({
  imports: [
    TypeOrmModule.forFeature([User]),
    PassportModule.register({ defaultStrategy: 'jwt' }),
    forwardRef(() => AuthModule),
    forwardRef(() => UsersModule),
    UserStatusModule,
  ],
  controllers: [GameController],
  providers: [GameService, GameGateway, GameEnv],
  exports: [PassportModule, GameGateway],
})
export class GameModule {}
