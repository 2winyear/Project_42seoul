import { IChallengeResponse, GameMode, IGameRoomInfo, IGameRooms } from '../utils/interface';
import { instance } from './index';

const gamePath = (path: string): string => {
  return `/games${path}`;
};

const gameAPI = {
  // GET /games - getGameRooms
  getGameRooms: async (jwt: string): Promise<IGameRooms[] | []> => {
    try {
      const url = gamePath('');
      const res = await instance.get(url, {
        headers: { Authorization: `Bearer ${jwt}` },
      });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return [];
    }
  },
  // POST /games - makeGameRoom
  makeGameRoom: async (
    ownerId: number,
    roomTitle: string,
    password: string | null,
    gameMode: GameMode,
    jwt: string,
  ): Promise<IGameRoomInfo | null> => {
    try {
      const url = gamePath(`/${ownerId}`);
      const res = await instance.post(
        url,
        { ownerId, roomTitle, password, gameMode },
        { headers: { Authorization: `Bearer ${jwt}` } },
      );
      return res.data;
    } catch (e) {
      if (e instanceof Error) {
        console.error(e.message);
        console.dir(e);
      } else console.error(e);
      return null;
    }
  },
  // GET /games/{gameId}/users - getMatchingUser(socket io로 제작)
  // getMatchingUser: async (gameId: number, jwt: string) => {
  //   try {
  //     const url = gamePath(`/${gameId}/users`);
  //     // const res = await instance.
  //     // return res.data;
  //   } catch (e) {
  //     if (e instanceof Error) console.error(e.message);
  //     else console.error(e);
  //   }
  // },
  // POST /games/{gameId}/users/{userId} - enterGameRoom

  // 이쪽도 수정이 필요하긴 하겠다.
  enterGameRoom: async (
    gameId: number,
    userId: number,
    password: string,
    jwt: string,
  ): Promise<IGameRoomInfo | null> => {
    try {
      const url = gamePath(`/${gameId}/users/${userId}`);
      const res = await instance.post(
        url,
        { password: password === '' ? null : password }, //지호킴님 수정요청111
        { headers: { Authorization: `Bearer ${jwt}` } },
      );
      return res.data;
    } catch (e) {
      if (e instanceof Error) {
        console.error(e.message);
        console.dir(e);
      } else console.error(e);
      return null;
    }
  },
  // DELETE /games/{gameId}/users/{userId} - leaveGameRoom
  leaveGameRoom: async (gameId: number, userId: number, jwt: string): Promise<void> => {
    try {
      const url = gamePath(`/${gameId}/users/${userId}`);
      await instance.delete(url, { headers: { Authorization: `Bearer ${jwt}` } });
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
    }
  },
  /**
   * 프로필 모달에서 대전 신청하기
   * @param userId 대전 신청한 유저
   * @param targetId 대전 신청당한 유저
   * @param jwt
   * @returns 대전 신청 가능한 상대면 true, 아니면 false
   */
  dieDieMatch: async (
    userId: number,
    targetId: number,
    jwt: string,
  ): Promise<IChallengeResponse> => {
    try {
      const url = gamePath(`/dieDieMatch/${userId}?targetId=${targetId}`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return {
        available: false,
        blocked: false,
        status: 'off',
      };
    }
  },

  // 상대유저의 세부상태?
  opponentState: async (targetId: number, jwt: string): Promise<IGameRooms | null> => {
    try {
      const url = gamePath(`/${targetId}`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
};

export { gameAPI };
