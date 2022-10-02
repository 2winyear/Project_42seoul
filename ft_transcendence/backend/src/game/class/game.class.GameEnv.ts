import { forwardRef, Inject, Injectable } from '@nestjs/common';
import { Socket } from 'socket.io';
import {
  ChallengeResponseDto,
  CreateGameRoomDto,
  GameRoomProfileDto,
} from '../dto/game.dto';
import { Player } from './game.class.Player';
import { GameAttribute } from './game.class.GameAttribute';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from 'src/users/entities/users.entity';
import { GameRecord } from 'src/users/entities/gameRecord.entity';
import { GameInfo } from './game.class.interface';
import { UserStatusContainer } from 'src/userStatus/userStatus.service';
import { GameQueue } from './game.class.GameQueue';
import { EventEmitter } from 'stream';
import { UsersService } from 'src/users/users.service';

@Injectable()
export class GameEnv {
  eventObject: EventEmitter = new EventEmitter();
  socketIdToPlayerMap = new Map<string, Player>();
  playerList: Player[] = [];
  gameLobbyTable: Map<number, Socket> = new Map();
  gameRoomList: GameAttribute[] = new Array(100);
  ladderQueue: GameQueue = new GameQueue('ladderQueue', this.eventObject);

  constructor(
    @InjectRepository(User)
    private readonly userRepo: Repository<User>,
    @Inject(forwardRef(() => UsersService))
    private usersService: UsersService,
    @Inject(forwardRef(() => UserStatusContainer))
    private userStats: UserStatusContainer,
  ) {
    for (let index = 0; index < 100; index++) {
      this.gameRoomList[index] = new GameAttribute(index + 1);
    }
    this.eventObject.on('makeLadderMatch', (p1, p2, mode) => {
      this.makeLadderMatch(p1, p2, mode);
    });
  }

  //
  // socketMap related methods

  getPlayerBySocket(socket: Socket): Player {
    return this.socketIdToPlayerMap.get(socket.id);
  }

  async getUserBySocket(socket: Socket): Promise<User> {
    const player: Player = this.socketIdToPlayerMap[socket.id];
    const user = await this.userRepo.findOne({ where: { id: player.userId } });
    return user;
  }

  getSocketIdByUserId(userId: number): string {
    let socket: string;
    this.socketIdToPlayerMap.forEach((value, key) => {
      if (value.userId === userId) socket = key;
    });
    return socket;
  }

  getLobbySocketOfUserId(userId: number): Socket {
    return this.gameLobbyTable.get(userId);
  }

  getSocketsOfIds(targets: number[]): Socket[] {
    const result: Socket[] = [];

    for (const finding of targets) {
      const member = this.gameLobbyTable.get(finding);
      if (member) result.push(member);
    }
    return result;
  }

  async assertGetPlayerBySocket(
    client: Socket,
    userId: number,
  ): Promise<Player> {
    let player = this.getPlayerBySocket(client);
    if (!player) {
      console.log(`unregistered userId ${userId}`);
      player = await this.newPlayer(userId, null);
      this.socketIdToPlayerMap.set(client.id, player);
    }
    return player;
  }

  eraseFromSocketMap(client: Socket): void {
    this.socketIdToPlayerMap.delete(client.id);
  }

  //
  // gameRoom* related methods

  getFreeGameRoom(): GameAttribute {
    for (const game of this.gameRoomList) {
      if (game.active === false) {
        return game;
      }
    }
    return null;
  }

  getGameRoom(gameId: number): GameAttribute {
    return this.gameRoomList.at(gameId - 1);
  }

  getPublicGameList(): GameRoomProfileDto[] {
    return this.gameRoomList
      .filter((game) => game.active && !game.isLadder)
      .map((game) => {
        return game.toGameRoomProfileDto();
      });
  }

  getGameOfPlayer(player: Player): GameRoomProfileDto {
    if (!player?.gamePlaying) {
      return undefined;
    }
    return player?.gamePlaying.toGameRoomProfileDto();
  }

  //
  // basic getters

  async getUserByUserId(userId: number): Promise<User> {
    return this.userRepo.findOneBy({ id: userId });
  }

  async getUserByPlayer(player: Player): Promise<User> {
    if (!player) return undefined;
    return this.userRepo.findOneBy({ id: player.userId });
  }

  async getPlayerByUserId(userId: number): Promise<Player> {
    const player = this.playerList.find((player) => {
      return player.userId === userId;
    });
    if (!player) return this.newPlayer(userId, null);
    else return player;
  }

  async newPlayer(userId: number, game: GameAttribute): Promise<Player> {
    for (const player of this.playerList) {
      if (player.userId === userId) {
        return player;
      }
    }
    const user = await this.userRepo.findOne({ where: { id: userId } });
    if (!user) {
      return undefined;
    }

    const newPlayer = new Player(user, game);
    this.playerList.push(newPlayer);
    return newPlayer;
  }

  //
  // socket connection managing methods
  // 소켓 연결 전에, 소켓을 제외한 모든 셋업은 api를 통해 처리되어 있어야 함.

  handleConnectionOnLobby(client: Socket, player: Player): void {
    if (!client || !player) return;
    this.gameLobbyTable.set(player.userId, client);
    client.join('gameLobby');

    player.socketLobbySet.add(client);

    this.userStats.setSocket(player.userId, client);
  }

  handleDisconnectionOnLobby(client: Socket, player: Player): void {
    if (!client || !player) return;
    player.socketLobbySet.delete(client);
    this.gameLobbyTable.delete(player.userId);

    this.userStats.removeSocket(client);
  }

  async handleConnectionOnDuel(client: Socket, player: Player): Promise<void> {
    if (!client || !player) return;
    const opponentId: number = +client.handshake.query['targetId'];
    const isChallenger = client.handshake.query['isSender'];
    if (opponentId == NaN) {
      console.log('handleConnectionOnDuel: no opponent');
      return;
    }
    player.socketQueue = client;

    if (isChallenger == 'true') {
      // 대전 신청을 보내는 쪽이면

      const notifying: Socket[] = this.userStats.getSockets(opponentId);
      for (const sock of notifying) {
        sock.emit('challengeDuelFrom', player.userId);
      }
      client.once('acceptChallenge', async () => {
        const opponent = await this.getPlayerByUserId(opponentId);
        if (!opponent) return;
        this.makeDuelMatch(player, opponent, 'normal');
        for (const sock of notifying) {
          // 이 이벤트를 받으면 대전 관련 창을 끄세여
          sock.emit('challengeAccepted', player.userId);
        }
      });
      return;
    }

    // 대전 신청을 받는 쪽이면
    client.once('acceptChallenge', async () => {
      const opponent = await this.getPlayerByUserId(opponentId);
      if (!opponent) return;
      opponent.socketQueue?.emit('acceptChallenge');
    });
  }

  async handleDisconnectionOnDuel(
    client: Socket,
    player: Player,
  ): Promise<void> {
    if (!client || !player) return;
    const opponentId: number = +client.handshake.query['targetId'];
    const opponent = await this.getPlayerByUserId(opponentId);
    const isChallenger = client.handshake.query['isSender'];
    if (!opponent) {
      console.log('handleDisconnectionOnDuel: no opponent');
      return;
    }

    const notifying: Socket[] = this.userStats.getSockets(opponentId);
    if (isChallenger == 'true') {
      for (const sock of notifying) {
        sock.emit('challengeSeqDone', player.userId);
      }
    }

    opponent.socketQueue?.emit('challengeRejected', player.userId);
    player.socketQueue = null;
  }

  async handleConnectionOnLadderQueue(
    client: Socket,
    player: Player,
  ): Promise<void> {
    if (!client || !player) return;
    player.socketQueue = client;
    const queueLength = this.ladderQueue.enlist(player);
    console.log(`enlistLadderQueue: length: ${queueLength}`);
  }

  handleDisconnectionOnLadderQueue(client: Socket, player: Player): void {
    if (!client || !player) return;
    player.socketQueue = null;
    this.eraseFromSocketMap(client);
    this.ladderQueue.remove(player);
  }

  handleConnectionOnLadderGame(client: Socket, player: Player): void {
    if (!client || !player) return;
    const game = player.gamePlaying;

    player.setGameSocket(game, client);
    this.setSocketJoin(client, game);

    this.userStats.setSocket(player.userId, client);
  }

  handleDisconnectionOnLadderGame(client: Socket, player: Player): void {
    if (!client || !player) return;
    this.clearPlayerSocket(client);

    this.userStats.removeSocket(client);
  }

  handleConnectionOnNormalGame(
    client: Socket,
    gameId: number,
    player: Player,
  ): void {
    if (!gameId) {
      console.log(`connection: New client has no gameId`);
      client.send('no gameId');
      return;
    }
    const game = this.getGameRoom(gameId);
    if (
      game.firstPlayer !== player &&
      game.secondPlayer !== player &&
      !game.watchers.has(player)
    )
      return;
    if (player.gamePlaying !== game && !player.gamesWatching.has(game)) return;

    player.setGameSocket(game, client);
    this.setSocketJoin(client, game);

    this.userStats.setSocket(player.userId, client);
  }

  handleDisconnectionOnNormalGame(client: Socket, player: Player): void {
    this.clearPlayerSocket(client);

    this.userStats.removeSocket(client);
  }

  async onFirstSocketHandshake(
    client: Socket,
    userId: number,
    gameId: number,
    connectionType: string,
  ): Promise<void> {
    if (!(await this.userRepo.findOneBy({ id: userId }))) return;
    const player = await this.assertGetPlayerBySocket(client, userId);
    this.socketIdToPlayerMap[client.id] = player;

    switch (connectionType) {
      case 'gameLobby':
        this.handleConnectionOnLobby(client, player);
        break;
      case 'duel':
        this.handleConnectionOnDuel(client, player);
        break;
      case 'ladderQueue':
        this.handleConnectionOnLadderQueue(client, player);
        break;
      case 'ladderGame':
        this.handleConnectionOnLadderGame(client, player);
        break;
      case 'normalGame':
        this.handleConnectionOnNormalGame(client, gameId, player);
        break;
      default:
        const message = `ConnectionHandler: ${connectionType} is not a correct type of connection.`;
        console.log(message);
        client.send(message);
    }
    console.log(
      `New client connected: ${client.id.slice(
        0,
        6,
      )} ${connectionType} user:${userId} game:${gameId}`,
    );
    client.send(
      `New client connected: ${client.id.slice(
        0,
        6,
      )} ${connectionType} user:${userId} game:${gameId}`,
    );
  }

  onSocketDisconnect(
    client: Socket,
    connectionType: string,
    userId: number,
    gameId: number,
  ): void {
    const player = this.getPlayerBySocket(client);
    if (!player) {
      console.log('onSocketDisconnect: Cannot get Player with socket');
    }

    switch (connectionType) {
      case 'gameLobby':
        this.handleDisconnectionOnLobby(client, player);
        break;
      case 'duel':
        this.handleDisconnectionOnDuel(client, player);
        break;
      case 'ladderQueue':
        this.handleDisconnectionOnLadderQueue(client, player);
        break;
      case 'ladderGame':
        this.handleDisconnectionOnLadderGame(client, player);
        break;
      case 'normalGame':
        this.handleDisconnectionOnNormalGame(client, player);
        break;
      default:
        const message = `ConnectionHandler: ${connectionType} is not a correct type of connection.`;
        console.log(message);
        client.send(message);
    }
    console.log(
      `Client disconnected: ${client.id.slice(
        0,
        6,
      )} ${connectionType} user:${userId} game:${gameId}`,
    );
    client.send(
      `Client disconnected: ${client.id.slice(
        0,
        6,
      )} ${connectionType} user:${userId} game:${gameId}`,
    );
  }

  clearPlayerSocket(client: Socket): void {
    const player: Player = this.socketIdToPlayerMap[client.id];
    if (player === undefined) return;

    const game = player.socketsToGameMap.get(client);
    if (game) {
      // if (game.isPlaying === true) {
      //   player.unsetGameSocket(client);
      //   player.socketPlayingGame = undefined;
      //   return;
      // }
      if (game.isPlaying === true && player.socketPlayingGame === client) {
        const winner =
          game.firstPlayer === player ? game.secondPlayer : game.firstPlayer;
        this.terminateGame(game, winner);
      }
      player.unsetGameSocket(client);
      player.leaveGame(game);
    }

    this.eraseFromSocketMap(client);
    this.broadcastToLobby('updateGameRoomList', this.getPublicGameList());
  }

  //
  // game managing methods

  async isDuelAvailable(
    userId: number,
    opId: number,
  ): Promise<ChallengeResponseDto> {
    const player = await this.getPlayerByUserId(userId);
    const result = new ChallengeResponseDto();

    result.available = true;
    result.blocked = false;
    result.status = this.userStats.getStatus(userId);

    if (result.status !== 'on') {
      console.log('isDuelAvailable: user unavailable');
      result.available = false;
    } else if (player.socketQueue !== null) {
      console.log('isDuelAvailable: target is on queue');
      result.available = false;
    }
    if (await this.usersService.getBlockedUserById(opId, userId)) {
      result.available = false;
      result.blocked = true;
    }
    return result;
  }

  setTimerOfRoomCancel(game: GameAttribute): NodeJS.Timer {
    return setTimeout(() => {
      game.destroy();
    }, 5000);
  }

  createGameRoom(player: Player, createGameRoomDto: CreateGameRoomDto): number {
    const game = this.getFreeGameRoom();
    if (!game) return undefined;
    game.create(createGameRoomDto, player);
    player.gamePlaying = game;

    this.broadcastToLobby('updateGameRoomList', this.getPublicGameList());

    return game.roomId;
  }

  setSocketJoin(client: Socket, game: GameAttribute): void {
    if (!game) {
      console.log('setSocketJoin: game is undefined.');
      return;
    }
    client.join(game.roomId.toString());
  }

  joinPlayerToGame(player: Player, game: GameAttribute): number {
    player.joinGame(game);

    this.broadcastToLobby('updateGameRoomList', this.getPublicGameList());

    return game.playerCount;
  }

  broadcastToLobby(ev: string, ...args: any[]): void {
    if (this.gameLobbyTable.size === 0) {
      console.log('broadcastToLobby: No game lobby on connected');
      return;
    }
    const randomLobby: Socket = this.gameLobbyTable.values().next().value;
    randomLobby.to('gameLobby').emit(ev, ...args);
    randomLobby.emit(ev, ...args);
  }

  postGameProcedure(game: GameAttribute): void {
    if (game.isLadder === true) {
      game.destroy();
    } else {
      game.destroy();
      // game.initPlayData();
    }
    this.broadcastToLobby('updateGameRoomList', this.getPublicGameList());
    // clearInterval(this.streaming);
  }

  createCustomGame(p1: Player, p2: Player, gameMode: string): GameAttribute {
    if (!p1 || !p2) return undefined;

    const game = this.getFreeGameRoom();
    if (!game) {
      console.log('makeCustomMatch: Cannot get Empty Room');
      return undefined;
    }
    const createGameRoomDto = new CreateGameRoomDto();
    createGameRoomDto.roomTitle = `${p1.userId}: ${p1.user.nickname}, ${p2.userId}: ${p2.user.nickname}`;
    createGameRoomDto.password = null;
    createGameRoomDto.gameMode = gameMode as 'normal' | 'speed' | 'obstacle';
    createGameRoomDto.ownerId = p1.userId;

    game.create(createGameRoomDto, p1);
    game.secondPlayer = p2;
    game.playerCount = 2;

    p1.gamePlaying = game;
    p2.gamePlaying = game;
    return game;
  }

  makeDuelMatch(
    player1: Player,
    player2: Player,
    gameMode: string,
  ): GameAttribute {
    if (!player1 || !player2) return undefined;

    const game = this.createCustomGame(player1, player2, gameMode);
    game.roomTitle = `[ Duel ] ${player1.user.nickname} vs ${player2.user.nickname}`;

    console.log(`Duel match made: ${player1.userId}, ${player2.userId}`);

    player1.socketQueue?.emit('matchingGame', game.roomId.toString());
    player2.socketQueue?.emit('matchingGame', game.roomId.toString());

    this.broadcastToLobby('updateGameRoomList', this.getPublicGameList());

    return game;
  }

  async makeLadderMatch(
    player1: Player,
    player2: Player,
    gameMode: string,
  ): Promise<GameAttribute> {
    if (!player1 || !player2) {
      console.log(
        `makeLadderMatch: wrong param delivered. ${player1} ${player2}`,
      );
      return undefined;
    }

    const game = this.createCustomGame(player1, player2, gameMode);
    game.isLadder = true;

    console.log(`Ladder match made: ${player1.userId}, ${player2.userId}`);

    player1.socketQueue?.emit('matchingGame', game.roomId.toString());
    player2.socketQueue?.emit('matchingGame', game.roomId.toString());

    return game;
  }

  async waitForPlayerJoins(client: Socket, gameId: number): Promise<void> {
    const player = this.getPlayerBySocket(client);
    if (!player) return;
    const game = this.getGameRoom(gameId);
    const isRightGame = player.gamePlaying === game;
    if (!isRightGame && player.gamesWatching.get(game) !== client) {
      console.log(
        `waitForPlayerJoins: ${player.userId} sent wrong roomNo.${gameId}`,
      );
      client.send('Error: recieved wrong room number');
      return;
    }
    if (!game.firstPlayer) return;
    const player1asUser: User = await this.userRepo.findOne({
      where: { id: game.firstPlayer.userId },
    });
    const player2asUser: User = game.secondPlayer
      ? await this.userRepo.findOne({
          where: { id: game.secondPlayer.userId },
        })
      : undefined;

    if (game.isPlaying === true) {
      client.emit(
        'matchData',
        player1asUser.toGamerInfoDto(),
        player2asUser?.toGamerInfoDto(),
      );
      client.emit('gameStartCount', '0');
      return;
    }

    game.broadcastToRoom(
      'matchData',
      player1asUser.toGamerInfoDto(),
      player2asUser?.toGamerInfoDto(),
    );

    if (!player2asUser) return;

    const gameStart = await game.startCountdown();
    if (gameStart) {
      game.gameStart();
      this.broadcastToLobby('updateGameRoomList', this.getPublicGameList());
    }
  }

  async processRecievedRtData(client: Socket, data: GameInfo): Promise<void> {
    const player: Player = this.getPlayerBySocket(client);
    const game = player.gamePlaying;
    if (!game) return;

    game.updateRtData(data);
    if (game.isPlaying && game.isFinished()) {
      game.isPlaying = false;
      await this.endGame(game);
    }
    game.sendRtData();
  }

  async processRecievedPaddleRtData(
    client: Socket,
    data: number,
  ): Promise<void> {
    const player: Player = this.getPlayerBySocket(client);
    const game = player.gamePlaying;

    if (game) {
      game.updatePaddleRtData(data);
      game.sendRtData();
    }
  }

  async endGame(game: GameAttribute): Promise<void> {
    console.log(`game is finished ${game.roomId}`);
    game.broadcastToRoom('gameFinished');
    await this.writeMatchResult(game);
    this.postGameProcedure(game);
  }

  async terminateGame(game: GameAttribute, winner: Player): Promise<void> {
    let winSide: number;

    console.log(
      `game ${game.roomId} is terminated, winner is ${winner.userId}`,
    );
    if (winner === game.firstPlayer) {
      game.rtData.scoreLeft = 11;
      game.rtData.scoreRight = 0;
      winSide = 1;
    } else {
      game.rtData.scoreLeft = 0;
      game.rtData.scoreRight = 11;
      winSide = 2;
    }
    game.isPlaying = false;
    game.broadcastToRoom('gameTerminated', winSide);
    await this.writeMatchResult(game);
    this.postGameProcedure(game);
  }

  async writeMatchResult(game: GameAttribute): Promise<void> {
    const winnerId = game.getWinner().userId;

    const p1 = game.firstPlayer;
    const p2 = game.secondPlayer;
    const isLadder = game.isLadder;

    const newRecord = new GameRecord();
    newRecord.playerOneId = game.firstPlayer.userId;
    newRecord.playerOneScore = game.rtData.scoreLeft;
    newRecord.playerTwoId = game.secondPlayer.userId;
    newRecord.playerTwoScore = game.rtData.scoreRight;
    newRecord.winnerId = winnerId;
    newRecord.isLadder = isLadder;

    const firstPlayer = await this.getUserByPlayer(p1);
    const secondPlayer = await this.getUserByPlayer(p2);
    if (!firstPlayer || !secondPlayer) {
      console.log('writeMatchResult: cannot get user from the database');
      return;
    }

    if (winnerId === firstPlayer.id) {
      if (isLadder) {
        firstPlayer.ladderWinCount++;
        secondPlayer.ladderLoseCount++;
      } else {
        firstPlayer.winCount++;
        secondPlayer.loseCount++;
      }
    } else {
      if (isLadder) {
        secondPlayer.ladderWinCount++;
        firstPlayer.ladderLoseCount++;
      } else {
        secondPlayer.winCount++;
        firstPlayer.loseCount++;
      }
    }
    p1.user = firstPlayer;
    p2.user = secondPlayer;
    await firstPlayer.save();
    await secondPlayer.save();

    await newRecord.save();
  }
}
