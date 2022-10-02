import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  ParseIntPipe,
  Post,
  Query,
  UseGuards,
} from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { ApiBearerAuth, ApiOperation, ApiTags } from '@nestjs/swagger';
import { GetJwtUser } from '../auth/jwt.strategy';
import { User } from '../users/entities/users.entity';
import { GamerInfoDto } from '../users/dto/users.dto';
import {
  ChallengeResponseDto,
  CreateGameRoomDto,
  GameRoomPasswordDto,
  GameRoomProfileDto,
  SimpleGameRoomDto,
} from './dto/game.dto';
import { GameService } from './game.service';

@ApiTags('games')
@Controller('games')
@ApiBearerAuth('access-token')
@UseGuards(AuthGuard())
export class GameController {
  constructor(private gameService: GameService) {}

  @ApiOperation({ summary: 'seungyel✅ 게임방 목록 가져오기' })
  @Get('/')
  getGameRooms(): GameRoomProfileDto[] {
    return this.gameService.getGameRoomList();
  }

  @ApiOperation({ summary: '특정 유저가 참여중인 게임방 정보 가져오기' })
  @Get('/:userId')
  async getGameInfoOfUser(
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<GameRoomProfileDto> {
    return await this.gameService.getGameInfoOfUser(userId);
  }

  @ApiOperation({ summary: 'seungyel✅ 게임방 만들기' })
  @Post('/:userId')
  async createGameRoom(
    @GetJwtUser() user: User,
    @Param('userId') userId: number,
    @Body() createGameRoomDto: CreateGameRoomDto,
  ): Promise<SimpleGameRoomDto> {
    const gameRoom = this.gameService.createGameRoom(user, createGameRoomDto);
    return gameRoom;
  }

  @ApiOperation({ summary: 'seungyel✅ 게임방 참여자(플레이어) 정보 가져오기' })
  @Get('/:gameId/users')
  async getGameUsers(
    @Param('gameId', ParseIntPipe) gameId: number,
  ): Promise<GamerInfoDto[]> {
    return await this.gameService.getPlayersInfo(gameId);
  }

  @ApiOperation({ summary: 'seungyel✅ 게임방 입장하기' })
  @Post('/:gameId/users/:userId')
  async enterGameRoom(
    @GetJwtUser() user: User,
    @Param('gameId', ParseIntPipe) gameId: number,
    @Param('userId', ParseIntPipe) userId: number,
    @Body() gamePasswordDto: GameRoomPasswordDto,
  ): Promise<SimpleGameRoomDto> {
    return await this.gameService.enterGameRoom(
      user,
      gameId,
      userId,
      gamePasswordDto.password,
    );
  }

  @ApiOperation({ summary: 'seungyel✅ 게임방 퇴장하기' })
  @Delete('/:gameId/users/:userId')
  async exitGameRoom(
    @GetJwtUser() user: User,
    @Param('gameId', ParseIntPipe) gameId: number,
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<void> {
    await this.gameService.exitGameRoom(user, gameId, userId);
  }

  @ApiOperation({ summary: '대전신청' })
  @Get('/dieDieMatch/:userId')
  async challengeDuel(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) userId: number,
    @Query('targetId', ParseIntPipe) targetId: number,
  ): Promise<ChallengeResponseDto> {
    return await this.gameService.challengeDuel(user, userId, targetId);
  }
}
