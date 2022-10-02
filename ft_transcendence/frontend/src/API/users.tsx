import { instance } from './index';
import {
  IGameRecord,
  IUserWinLoseCount,
  IUserAvatar,
  IUserData,
  IGetUser,
} from '../utils/interface';

const usersPath = (path: string) => {
  return `/users${path}`;
};

const usersAPI = {
  // 이미지 업로드
  uploadAvatarImg: async (
    myId: number,
    body: FormData,
    jwt: string,
  ): Promise<IUserAvatar | null> => {
    try {
      const url = usersPath(`/${myId}/uploadImage`);
      const res = await instance.post(url, body, {
        headers: { ContentType: 'multipart/form-data', Authorization: `Bearer ${jwt}` },
      });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // 모든 유저의 id, 닉네임, 상태
  getAllUsersIdNickName: async (jwt: string): Promise<IGetUser[] | []> => {
    try {
      const url = usersPath(``);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return [];
    }
  },
  // 본인 정보 가져오기
  getLoginUserProfile: async (jwt: string): Promise<IUserData | null> => {
    // TODO: own 프로필 포멧이 변경됨...
    try {
      const url = usersPath(`/own`);
      const response = await instance.get(url, {
        headers: {
          Authorization: `Bearer ${jwt}`,
        },
      });
      return response.data;
    } catch (e) {
      if (e instanceof Error) {
        console.error(e.message);
      } else {
        console.error(e);
      }
      return null;
    }
  },
  // 특정 유저의 프로필 조회
  getUserProfile: async (
    myId: number,
    targetId: number,
    jwt: string,
  ): Promise<IUserData | null> => {
    try {
      const url = usersPath(`/${myId}?targetId=${targetId}`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // 친구 추가
  makeFriend: async (myId: number, followId: number, jwt: string): Promise<string | null> => {
    try {
      const url = usersPath(`/${myId}/friends`);
      const res = await instance.post(
        url,
        { followId },
        { headers: { Authorization: `Bearer ${jwt}` } },
      );
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // 친구 목록 조회
  getFriendList: async (myId: number, jwt: string): Promise<IGetUser[] | []> => {
    try {
      const url = usersPath(`/${myId}/friends`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return [];
    }
  },
  // 전적 조회
  getUserGameRecords: async (userId: number, jwt: string): Promise<IGameRecord[] | []> => {
    try {
      const url = usersPath(`/${userId}/gameRecords`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return [];
    }
  },
  // 닉네임 변경
  updateUserNickname: async (
    myId: number,
    nickname: string,
    jwt: string,
  ): Promise<IUserData | null> => {
    try {
      const url = usersPath(`/${myId}/nickname`);
      const res = await instance.put(
        url,
        { nickname },
        { headers: { Authorization: `Bearer ${jwt}` } },
      );
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // 유저의 승패 카운트 조회
  getUserWinLoseCount: async (userId: number, jwt: string): Promise<IUserWinLoseCount | null> => {
    try {
      const url = usersPath(`/${userId}/winLoseCount`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // 친구 삭제
  deleteFriend: async (myId: number, followId: number, jwt: string): Promise<string | null> => {
    try {
      const url = usersPath(`/${myId}/friends`);
      const res = await instance.delete(url, {
        data: { followId },
        headers: { Authorization: `Bearer ${jwt}` },
      });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // 유저 차단하기 토글
  toggleBlockUser: async (myId: number, targetId: number, jwt: string): Promise<boolean> => {
    // TODO: return type definine plz....
    try {
      const url = usersPath(`/${myId}`);
      const res = await instance.put(
        url,
        {
          targetId,
        },
        {
          headers: { Authorization: `Bearer ${jwt}` },
        },
      );
      return res.data.isBlocked;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return false;
    }
  },
};
export { usersAPI };
