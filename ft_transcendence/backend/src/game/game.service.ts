import { BadRequestException, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { GameRecord } from 'src/users/entities/gameRecord.entity';
import { User } from 'src/users/entities/users.entity';
import { Repository } from 'typeorm';
import { GamerInfoDto as PlayerInfoDto } from '../users/dto/users.dto';
import {
  CreateGameRoomDto,
  GameRoomProfileDto,
  GameResultDto,
  SimpleGameRoomDto,
  ChallengeResponseDto,
} from './dto/game.dto';
import { GameEnv } from './class/game.class.GameEnv';
import { UsersService } from 'src/users/users.service';

@Injectable()
export class GameService {
  constructor(
    @InjectRepository(User)
    private readonly userRepo: Repository<User>,
    private readonly usersService: UsersService,
    private readonly gameEnv: GameEnv,
  ) {}

  // HTTP APIs

  getGameRoomList(): GameRoomProfileDto[] {
    return this.gameEnv.getPublicGameList();
  }

  async getGameInfoOfUser(userId: number): Promise<GameRoomProfileDto> {
    const targetPlayer = await this.gameEnv.getPlayerByUserId(userId);
    if (!targetPlayer) {
      throw new BadRequestException('잘못된 유저id입니다.');
    }
    return this.gameEnv.getGameOfPlayer(targetPlayer);
  }

  async createGameRoom(
    user: User,
    createGameRoomDto: CreateGameRoomDto,
  ): Promise<SimpleGameRoomDto> {
    if (user.id !== createGameRoomDto.ownerId) {
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    }
    const player = await this.gameEnv.getPlayerByUserId(user.id);
    if (player.gamePlaying) {
      throw new BadRequestException(`이미 게임을 생성한 유저입니다.`);
    }

    const gameId = this.gameEnv.createGameRoom(player, createGameRoomDto);
    if (gameId === undefined)
      throw new BadRequestException(`최대 방 갯수를 초과하였습니다.`);

    const gameRoomDto = new SimpleGameRoomDto();
    gameRoomDto.gameMode = createGameRoomDto.gameMode;
    gameRoomDto.ownerId = createGameRoomDto.ownerId;
    gameRoomDto.roomTitle = createGameRoomDto.roomTitle;
    gameRoomDto.gameId = gameId;

    return gameRoomDto;
  }

  async getPlayersInfo(gameId: number): Promise<PlayerInfoDto[]> {
    const players: PlayerInfoDto[] = [];

    const gameRoom = this.gameEnv.getGameRoom(gameId);
    if (!gameRoom) throw new BadRequestException('방 정보를 찾을 수 없습니다.');

    const firstPlayerUserId = gameRoom.firstPlayer.userId;
    const firstPlayer = await this.userRepo.findOneBy({
      id: firstPlayerUserId,
    });
    players.push(firstPlayer.toGamerInfoDto());

    if (!gameRoom.secondPlayer) {
      return players;
    }

    const secondPlayerUserId = gameRoom.secondPlayer.userId;
    const secondPlayer = await this.userRepo.findOneBy({
      id: secondPlayerUserId,
    });
    players.push(secondPlayer.toGamerInfoDto());

    return players;
  }

  async enterGameRoom(
    user: User,
    gameId: number,
    userId: number,
    gamePassword: string | null,
  ): Promise<SimpleGameRoomDto> {
    if (user.id != userId)
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    const player = await this.gameEnv.getPlayerByUserId(userId);
    if (!player) throw new BadRequestException('플레이어 정보가 없습니다.');
    const game = this.gameEnv.getGameRoom(gameId);
    if (game == null) throw new BadRequestException('게임을 찾을 수 없습니다.');
    if (game.password != gamePassword)
      throw new BadRequestException('잘못된 비밀번호.');
    if (player.isJoinedGame(game))
      throw new BadRequestException('이미 입장 된 방입니다.');

    const peopleCount = this.gameEnv.joinPlayerToGame(player, game);
    console.log(
      `Player ${player.userId} joined room ${game.roomId}, ${peopleCount}`,
    );
    // 소켓: 로비에 변경사항 반영

    const gameRoomDto = new SimpleGameRoomDto();
    gameRoomDto.gameMode = game.gameMode;
    gameRoomDto.ownerId = game.ownerId;
    gameRoomDto.roomTitle = game.roomTitle;
    gameRoomDto.gameId = gameId;

    return gameRoomDto;
  }

  async exitGameRoom(
    user: User,
    gameId: number,
    userId: number,
  ): Promise<void> {
    if (user.id != userId)
      throw new BadRequestException('잘못된 유저의 접근입니다.');

    const game = this.gameEnv.getGameRoom(gameId);
    if (!game) {
      throw new BadRequestException('게임을 찾을 수 없습니다.');
    }

    const player = await this.gameEnv.getPlayerByUserId(userId);
    if (!player) {
      throw new BadRequestException('플레이어를 찾을 수 없습니다.');
    }

    if (game.isPlaying === true && player.gamePlaying === game) {
      const winner =
        game.firstPlayer === player ? game.secondPlayer : game.firstPlayer;
      this.gameEnv.terminateGame(game, winner);
    }
    player.leaveGame(game);
    this.gameEnv.broadcastToLobby(
      'updateGameRoomList',
      this.gameEnv.getPublicGameList(),
    );
  }

  async challengeDuel(
    user: User,
    userId: number,
    targetId: number,
  ): Promise<ChallengeResponseDto> {
    if (user.id != userId)
      throw new BadRequestException('잘못된 유저의 접근입니다.');
    if (userId === targetId)
      throw new BadRequestException('잘못된 요청입니다.');

    return await this.gameEnv.isDuelAvailable(userId, targetId);
  }

  async saveGameRecord(gameRecordSaveDto: GameResultDto): Promise<void> {
    const firstPlayer = await this.userRepo.findOneBy({
      id: gameRecordSaveDto.playerOneId,
    });
    const secondPlayer = await this.userRepo.findOneBy({
      id: gameRecordSaveDto.playerTwoId,
    });
    if (!firstPlayer || !secondPlayer) {
      throw new BadRequestException('유저 정보를 찾을 수 없습니다.');
    }
    if (gameRecordSaveDto.winnerId == gameRecordSaveDto.playerOneId) {
      if (gameRecordSaveDto.isLadder) {
        firstPlayer.ladderWinCount++;
        secondPlayer.ladderLoseCount++;
      } else {
        firstPlayer.winCount++;
        secondPlayer.loseCount++;
      }
    } else {
      if (gameRecordSaveDto.isLadder) {
        secondPlayer.ladderWinCount++;
        firstPlayer.ladderLoseCount++;
      } else {
        secondPlayer.winCount++;
        firstPlayer.loseCount++;
      }
    }
    const newRecord = new GameRecord();
    newRecord.playerOneId = gameRecordSaveDto.playerOneId;
    newRecord.playerOneScore = gameRecordSaveDto.playerOneScore;
    newRecord.playerTwoId = gameRecordSaveDto.playerTwoId;
    newRecord.playerTwoScore = gameRecordSaveDto.playerTwoScore;
    newRecord.winnerId = gameRecordSaveDto.winnerId;
    await newRecord.save();

    await firstPlayer.save();
    await secondPlayer.save();
  }
}
