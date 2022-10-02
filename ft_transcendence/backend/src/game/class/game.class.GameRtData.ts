import { randomInt } from 'crypto';
import { GameInfo } from './game.class.interface';

export class GameRtData {
  ball_pos: [number, number];
  ball_vec: [number, number];
  paddle_L_pos: number;
  paddle_R_pos: number;
  turn: number;
  lostPoint: boolean;
  updateFlag: boolean;
  player: number; //
  scoreLeft: number;
  scoreRight: number;
  lastSent: number;

  constructor() {
    this.ball_pos = [50, 50];
    this.ball_vec = [1, 0];
    this.paddle_L_pos = 0;
    this.paddle_R_pos = 0;
    this.turn = randomInt(2) + 1;
    this.lostPoint = false;
    this.updateFlag = true;
    this.scoreLeft = 0;
    this.scoreRight = 0;
    this.lastSent = Date.now();
    this.player = 1; //
  }

  toRtData(): (number | boolean)[] {
    const data = [
      this.ball_pos[0],
      this.ball_pos[1],
      this.ball_vec[0],
      this.ball_vec[1],
      this.paddle_L_pos,
      this.paddle_R_pos,
      this.turn,
      this.lostPoint,
      this.scoreLeft,
      this.scoreRight,
      this.player,
    ];

    return data;
  }

  toScoreData(): number[] {
    return [this.scoreLeft, this.scoreRight];
  }

  updateScore(): void {
    if (this.lostPoint == false) {
      return;
    }
    if (this.turn == 1) {
      this.scoreLeft += 1;
    } else {
      this.scoreRight += 1;
    }
    this.lostPoint = false;
  }

  updateRtData(data: GameInfo): void {
    this.ball_pos = [data.ballP_X, data.ballP_Y];
    this.ball_vec = [data.ballVelo_X, data.ballVelo_Y];
    this.turn = data.turn;
    this.player = data.player;
    if (this.turn == 1) {
      this.paddle_L_pos = data.leftPaddlePos;
    } else {
      this.paddle_R_pos = data.rightPaddlePos;
    }
    this.lostPoint = data.checkPoint;
    this.updateFlag = true;
    this.updateScore();
  }

  updatePaddleRtData(data: number): void {
    if (this.turn == 1) {
      this.paddle_R_pos = data;
    } else {
      this.paddle_L_pos = data;
    }
  }

  isReadyToSend(): boolean {
    const currentTime = Date.now();
    const result = this.updateFlag == true && currentTime - this.lastSent > 15;
    if (result === true) this.lastSent = currentTime;
    return result;
  }
}
