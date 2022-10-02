import { EventEmitter } from 'stream';
import { clearInterval, setInterval } from 'timers';
import { Player } from './game.class.Player';

class QueueInfo {
  player: Player;
  gentime: number;
  priority: number;
  gapAllow: number;
  picked: boolean;

  constructor(player: Player) {
    this.player = player;
    this.gentime = new Date().getTime();
    this.priority = 0;
    this.gapAllow = 5;
    this.picked = false;
  }
}

export class GameQueue {
  name: string;
  queue: QueueInfo[];
  eventObject: EventEmitter;
  matching: NodeJS.Timer;

  constructor(name: string, eventObj: EventEmitter) {
    this.name = name;
    this.queue = [];
    this.eventObject = eventObj;

    this.eventObject.on(`${name}`, this.pickMatchup);
  }

  enlist(player: Player): number {
    const item = new QueueInfo(player);
    if (this.lookFor(player)) return this.queue.length;

    const length = this.queue.push(item);
    this.switchMatchMaker();
    return length;
  }

  lookFor(player: Player): QueueInfo {
    const item = this.queue.find((queue) => {
      return queue.player === player;
    });
    return item;
  }

  remove(player: Player): boolean {
    const queueItem = this.lookFor(player);
    const index = this.queue.indexOf(queueItem);

    if (index === -1) return false;

    this.queue.splice(index, 1);
    this.switchMatchMaker();
    return true;
  }

  switchMatchMaker(): void {
    if (this.matching) {
      if (this.queue.length < 2) {
        clearInterval(this.matching);
        this.matching = null;
        console.log('switchMatchMaker: matching off');
      }
      return;
    }
    if (this.queue.length >= 2) {
      this.matching = setInterval(() => {
        this.pickMatchup();
      }, 100);
    }
    console.log('switchMatchMaker: matching on');
  }

  compareElements(one: QueueInfo, two: QueueInfo): boolean {
    const oneLevel = one.player.user.getLadderLevel();
    const oneMinLevel =
      oneLevel - one.gapAllow < 0 ? 0 : oneLevel - one.gapAllow;
    const oneMaxLevel = oneLevel + one.gapAllow;
    const twoLevel = two.player.user.getLadderLevel();
    const twoMinLevel =
      twoLevel - two.gapAllow < 0 ? 0 : twoLevel - two.gapAllow;
    const twoMaxLevel = twoLevel + two.gapAllow;

    return (
      (oneMinLevel <= twoMaxLevel && oneMinLevel >= twoMinLevel) ||
      (oneMaxLevel >= twoMinLevel && oneMaxLevel <= twoMaxLevel)
    );
  }

  findMatchableOfOne(one: QueueInfo): QueueInfo {
    const filteredQ = this.queue.filter((value) => {
      if (value === one) return false;
      return this.compareElements(one, value);
    });
    if (filteredQ.length === 0) return undefined;

    filteredQ.sort((a, b) => {
      return a.gentime - b.gentime;
    });

    return filteredQ.at(0);
  }

  matchAlgorithm(players: Player[]): boolean {
    const calltime = new Date().getTime();

    this.queue.forEach((value) => {
      switch (Math.floor((calltime - value.gentime) / 1000)) {
        case 0:
          break;
        case 1:
          value.priority = 1;
          value.gapAllow = 5 * Math.pow(2, 1);
          break;
        case 2:
          value.priority = 2;
          value.gapAllow = 5 * Math.pow(2, 2);
          break;
        case 3:
          value.priority = 3;
          value.gapAllow = 5 * Math.pow(2, 3);
          break;
        case 4:
          value.priority = 4;
          value.gapAllow = 5 * Math.pow(2, 4);
          break;
        case 5:
          value.priority = 5;
          value.gapAllow = 5 * Math.pow(2, 5);
          break;
        case 6:
          value.priority = 6;
          value.gapAllow = 5 * Math.pow(2, 6);
          break;
        default:
          value.priority = 7;
          value.gapAllow = Number.POSITIVE_INFINITY;
      }
    });

    if (this.queue.length < 2) return false;

    for (const element of this.queue) {
      const opponent = this.findMatchableOfOne(element);
      if (!opponent) continue;
      players.push(element.player);
      if (element.gentime <= opponent.gentime) {
        players.push(opponent.player);
      } else {
        players.unshift(opponent.player);
      }
      this.queue.splice(this.queue.indexOf(element), 1);
      this.queue.splice(this.queue.indexOf(opponent), 1);
      this.switchMatchMaker();
      return true;
    }
    return false;
  }

  pickMatchup(): void {
    const inittime = new Date().getTime();
    const players: Player[] = [];
    let matched = this.matchAlgorithm(players);

    while (new Date().getTime() - inittime < 100 && matched === true) {
      this.eventObject.emit(
        'makeLadderMatch',
        players[0],
        players[1],
        'normal',
      );
      console.log(`ladderMatching: ${players}`);

      matched = this.matchAlgorithm(players);
    }

    this.switchMatchMaker();
  }
}
