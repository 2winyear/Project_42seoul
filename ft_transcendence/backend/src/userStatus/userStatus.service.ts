import { forwardRef, Inject, Injectable } from '@nestjs/common';
import { Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';

class UserStatus {
  constructor(userId: number) {
    this.userId = userId;
    this.status = 'off';
    this.chatLobbySockets = new Set();
    this.chatSockets = new Set();
    this.gameLobbySockets = new Set();
    this.gamePlayingSockets = new Set();
    this.gameWatchingSockets = new Set();
  }
  userId: number;
  status: 'on' | 'off' | 'play';
  chatLobbySockets: Set<Socket>;
  chatSockets: Set<Socket>;
  gameLobbySockets: Set<Socket>;
  gamePlayingSockets: Set<Socket>;
  gameWatchingSockets: Set<Socket>;

  isGameConnection(socket: Socket): boolean {
    return (
      socket.handshake.query['connectionType'] == 'ladderGame' ||
      socket.handshake.query['connectionType'] == 'normalGame'
    );
  }

  isGamePlaying(socket: Socket): boolean {
    return socket.rooms.has('playing');
  }

  setSocket(socket: Socket): void {
    if (socket.nsp.name == '/ws-chatLobby') this.chatLobbySockets.add(socket);
    else if (socket.nsp.name == '/ws-chat') this.chatSockets.add(socket);
    else if (socket.handshake.query['connectionType'] == 'gameLobby')
      this.gameLobbySockets.add(socket);
    else if (this.isGameConnection(socket)) {
      if (this.isGamePlaying(socket)) this.gamePlayingSockets.add(socket);
      else this.gameWatchingSockets.add(socket);
    } else console.log('UserStatus: setSocket: wrong socket');
  }

  removeSocket(socket: Socket): boolean {
    let result = false;
    result ||= this.chatLobbySockets.delete(socket);
    result ||= this.chatSockets.delete(socket);
    result ||= this.gameLobbySockets.delete(socket);
    result ||= this.gamePlayingSockets.delete(socket);
    result ||= this.gameWatchingSockets.delete(socket);
    return result;
  }

  private _pruneSocketSet(socketSet: Set<Socket>): boolean {
    let result = false;
    for (const sock of socketSet) {
      if (sock.connected === false) {
        socketSet.delete(sock);
        result = true;
      }
    }
    return result;
  }
  pruneSocket(): boolean {
    let result = false;
    result ||= this._pruneSocketSet(this.chatLobbySockets);
    result ||= this._pruneSocketSet(this.chatSockets);
    result ||= this._pruneSocketSet(this.gameLobbySockets);
    result ||= this._pruneSocketSet(this.gamePlayingSockets);
    result ||= this._pruneSocketSet(this.gameWatchingSockets);
    return result;
  }

  getSockets(): Socket[] {
    const found: Socket[] = [];

    for (const socket of this.chatLobbySockets.values()) {
      found.push(socket);
    }
    for (const socket of this.chatSockets.values()) {
      found.push(socket);
    }
    for (const socket of this.gameLobbySockets.values()) {
      found.push(socket);
    }
    for (const socket of this.gameWatchingSockets.values()) {
      found.push(socket);
    }
    return found;
  }

  changeStatus(): boolean {
    const lastStatus = this.status;

    if (this.gamePlayingSockets.size !== 0) this.status = 'play';
    else if (
      this.chatLobbySockets.size !== 0 ||
      this.chatSockets.size !== 0 ||
      this.gameLobbySockets.size !== 0 ||
      this.gameWatchingSockets.size !== 0
    )
      this.status = 'on';
    else this.status = 'off';

    console.log(this);
    return this.status !== lastStatus;
  }

  broadcastToLobbies(ev: string, ...args: any[]): void {
    for (const cLobby of this.chatLobbySockets) {
      cLobby.broadcast.emit(ev, ...args);
      cLobby.emit(ev, ...args);
    }
    for (const gLobby of this.gameLobbySockets) {
      gLobby.to('gameLobby').emit(ev, ...args);
      gLobby.emit(ev, ...args);
    }
  }
}

@Injectable()
export class UserStatusContainer {
  constructor(
    @Inject(forwardRef(() => AuthService))
    private readonly authService: AuthService,
  ) {
    for (let index = 0; index < 1000; index++) {
      this.userContainer[index] = new UserStatus(index);
    }
  }

  userContainer: UserStatus[] = new Array(1000);

  get(userId: number): UserStatus {
    return this.userContainer.at(userId);
  }

  getStatus(userId: number): 'on' | 'off' | 'play' {
    return this.get(userId).status;
  }

  getSockets(userId: number): Socket[] {
    return this.get(userId).getSockets();
  }

  // return: 유저상태 변경 여부
  async setSocket(
    userId: number,
    socket: Socket,
    callIfStatusChanged?: () => void,
  ): Promise<boolean> {
    this.get(userId).setSocket(socket);

    const isStatusChanged = this.get(userId).changeStatus();
    if (isStatusChanged) {
      await this.authService.emitUpdatedUserList(userId);
      callIfStatusChanged;
    }
    return isStatusChanged;
  }

  async removeSocketOfUser(
    userId: number,
    socket: Socket,
    callIfStatusChanged?: () => void,
  ): Promise<boolean> {
    this.get(userId).removeSocket(socket);

    const isStatusChanged = this.get(userId).changeStatus();
    if (isStatusChanged) {
      await this.authService.emitUpdatedUserList(userId);
      callIfStatusChanged;
    }
    return isStatusChanged;
  }

  async removeSocket(
    socket: Socket,
    callIfStatusChanged?: () => void,
  ): Promise<boolean> {
    let result: boolean;
    for (const user of this.userContainer) {
      if (user.status === 'off') continue;

      result = user.removeSocket(socket);

      if (user.pruneSocket() === true) {
        console.log(':::userStatusManager:::');
        console.log('Dangling Dead Socket has been pruned Automatically.');
      }

      if (user.changeStatus()) {
        await this.authService.emitUpdatedUserList(user.userId);
        callIfStatusChanged;
      }
    }
    return result;
  }

  pruneSocket(): boolean {
    let result = false;
    for (const user of this.userContainer) {
      if (user.status === 'off') continue;
      result ||= user.pruneSocket();
    }
    return result;
  }
}
