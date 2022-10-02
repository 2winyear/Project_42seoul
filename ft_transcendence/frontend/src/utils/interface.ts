import { Socket } from 'socket.io-client';

export interface IUserKey {
  userId: number;
  nickname: string;
  socket: Socket;
}

export interface IUser extends IUserKey {
  email: string;
  avatar: string;
}
export interface IUserAuth extends IUser {
  isSecondAuthOn: boolean;
  jwt: string;
}

// export interface IGetUserProfile extends IUserProfile {
//   isSecondAuthOn: boolean;
//   isFriend: boolean;
//   isBlocked: boolean;
// }
export interface IChatRoomInfo {
  roomId: number;
  title: string;
  ownerId: number;
  isDm?: boolean;
}
export interface IChatDMRoom extends IChatRoomInfo {}
export interface IGameRoomInfo {
  gameId: number;
  gameMode: GameMode;
  ownerId: number;
  roomTitle: string;
}
export interface IChatRooms {
  roomId: number;
  title: string;
  isPublic: boolean;
  ownerId: number;
  numberOfParticipants: number;
  isDm: boolean;
}
export interface IGameRooms {
  gameId: number;
  roomTitle: string;
  playerCount: number;
  isPublic: boolean;
  isStart: boolean;
}

export interface IRoomSetting {
  title: string;
  isDm?: boolean; // TODO: 수정될 예정
  password: string;
}

// export interface IParticipants extends IUserKey {
//   role: string;
// }

export const ALL = 'ALL' as const;
export const JOINED = 'JOINED' as const;

export type ChatRoomType = 'ALL' | 'JOINED';

// TODO: delete IRoomList
// export interface IRoomList {
//   id: number;
//   title: string;
//   isPublic: boolean;
//   playerCount: number;
//   isLadder: boolean;
//   isGameStart?: boolean;
// }
export interface IWinLoseCount {
  winCount: number;
  loseCount: number;
  ladderWinCount: number;
  ladderLoseCount: number;
  ladderLevel: number;
}
export interface IUserData extends IUserAuth, IWinLoseCount {
  isFriend: boolean;
  isBlocked: boolean;
}

// 여기서 모드를 저장한다면 어떨까. 아 그럼 래더시작할때는 또, 노말로 바꿔줘야되는거 아녀.
export interface IPlayingGameInfo {
  player: string;
  oneNickname: string;
  twoNickname: string;
  gameRoomId: number; // user.roomid -> ??.gameRoomId
  gameMode: string; // test!!
  gameLadder: boolean; // test!!
  gameState: boolean; //test!!!!
}

export interface IUserWinLoseCount extends IWinLoseCount {
  id: number;
}

export interface IGameRecord {
  isLadder: true;
  isWin: true;
  opponentNickname: string;
}
export interface IFollowId {
  followId: number;
}

export interface INickname {
  nickname: string;
}

export interface IUserAvatar {
  originalname: string;
  filename: string;
  UpdateImg: string;
}

export interface IChallengeResponse {
  available: boolean;
  blocked: boolean; // false 정상, true 차단당함
  status: 'on' | 'off' | 'play';
}

export interface IMessage {
  isBroadcast: boolean;
  userId: number;
  nickname: string;
  avatar: string; // TODO: 백쪽에서 아직 전달을 안해줌, null인 경우 기본 이미지
  message: string;
  createdTime: string;
}

export type ButtonColorType = 'white' | 'white2' | 'main' | 'gradient';

export interface IGetUser {
  userId: number;
  nickname: string;
  role?: string;
  status: 'on' | 'off' | 'play';
}
export type UserRole = 'owner' | 'manager' | 'guest';

export type ActiveMenuType = 'ALL' | 'FRIEND' | 'INCHAT';

export type GameMode = 'normal' | 'speed' | 'obstacle';

export const ON = 'on' as const;
export const OFF = 'off' as const;
export const PLAY = 'play' as const;

export const LOGIN = 'LOGIN' as const;
export const LOGOUT = 'LOGOUT' as const;
export const UPDATE_USER = 'UPDATE_USER' as const;
export const UPDATE_RECORD = 'UPDATE_RECORD' as const;
export const SET_NICKNAME = 'SET_NICKNAME' as const;
export const SECOND_AUTH = 'SECOND_AUTH' as const;
export const LOADING = 'LOADING' as const;

export type UserStatusType = 'LOGIN' | 'LOGOUT' | 'SET_NICKNAME' | 'SECOND_AUTH' | 'LOADING';
export type HandleUserType = 'LOGIN' | 'LOGOUT' | 'UPDATE_USER' | 'UPDATE_RECORD';

export const GAME = 'GAME' as const;
export const CHAT = 'CHAT' as const;
export const HOME = 'HOME' as const;

export type MenuType = 'GAME' | 'CHAT';

export const SHOW_PROFILE = 'SHOW_PROFILE' as const;
export const ON_SECOND_AUTH = 'ON_SECOND_AUTH' as const;
export const OFF_SECOND_AUTH = 'OFF_SECOND_AUTH' as const;
export const EDIT_NICKNAME = 'EDIT_NICKNAME' as const;
export const MAKE_GAME_ROOM = 'MAKE_GAME_ROOM' as const;
export const MAKE_CHAT_ROOM = 'MAKE_CHAT_ROOM' as const;
export const ENTER_GAME_ROOM = 'ENTER_GAME_ROOM' as const;
export const ENTER_CHAT_ROOM = 'ENTER_CHAT_ROOM' as const;
export const CHECK_SCORE = 'CHECK_SCORE' as const;
export const LOADING_LADDER_GAME = 'LOADING_LADDER_GAME' as const;
export const EDIT_CHAT_ROOM = 'EDIT_CHAT_ROOM' as const;
export const SHOW_OWNER_PROFILE = 'SHOW_OWNER_PROFILE' as const;
export const SHOW_MANAGER_PROFILE = 'SHOW_MANAGER_PROFILE' as const;
export const CHECK_LOGOUT = 'CHECK_LOGOUT' as const;
export const FIGHT_RES_MODAL = 'FIGHT_RES_MODAL' as const;
export const FIGHT_REQ_MODAL = 'FIGHT_REQ_MODAL' as const;
export const EDIT_MY_PROFILE = 'EDIT_MY_PROFILE' as const;
export const BAN_THIS_CHATROOM = 'BAN_THIS_CHATROOM' as const;
export const BAN_OR_KICK_MODAL = 'BAN_OR_KICK_MODAL' as const;
export const NOTI_OWNER_IN_CHATROOM = 'NOTI_OWNER_IN_CHATROOM' as const;
export const CANCEL_MATCH_MODAL = 'CANCEL_MATCH_MODAL' as const;

export type ModalType =
  | 'SHOW_PROFILE' // 프로필 정보 보기
  | 'ON_SECOND_AUTH' // 2차 인증 켜기
  | 'OFF_SECOND_AUTH' // 2차 인증 끄기
  | 'EDIT_NICKNAME' // 닉네임 수정
  | 'MAKE_GAME_ROOM' // 게임방 만들기
  | 'MAKE_CHAT_ROOM' // 채팅방 만들기
  | 'ENTER_GAME_ROOM' // 비밀 게임방 입장
  | 'ENTER_CHAT_ROOM' // 비밀 채팅방 입장
  | 'CHECK_SCORE' // 전적 확인
  | 'LOADING_LADDER_GAME' // 래더 게임 로딩
  | 'EDIT_CHAT_ROOM' // 채팅방 수정
  | 'SHOW_OWNER_PROFILE' // 채팅방 소유자 프로필
  | 'SHOW_MANAGER_PROFILE' // 채팅방 관리자 프로필
  | 'CHECK_LOGOUT' // 로그아웃 확인
  | 'FIGHT_RES_MODAL' // 1:1 대전 응답 모달
  | 'FIGHT_REQ_MODAL' // 1:1 대전 요청 모달
  | 'EDIT_MY_PROFILE' // 내 프로필 수정하기
  | 'BAN_THIS_CHATROOM' // 밴당한 채팅방 입장 경고 모달
  | 'BAN_OR_KICK_MODAL' // 강퇴 or 입장 금지 모달
  | 'CANCEL_MATCH_MODAL' // 대전 취소 모달
  | 'NOTI_OWNER_IN_CHATROOM'; // 방주인한테 갑질하려고 할때 뜨는 모달

export interface IModalData {
  modal: ModalType | null;
  roomId: number;
  userId: number;
}
