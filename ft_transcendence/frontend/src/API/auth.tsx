import { IUserAuth } from '../utils/interface';
import { instance } from './index';

const authPath = (path: string) => {
  return `/auth${path}`;
};

export const authAPI = {
  // 로그인시(유저의 회원 가입 여부 확인)
  isSignedUp: async (code: string): Promise<IUserAuth | null> => {
    try {
      const url = authPath(`/isSignedUp`);
      const response = await instance.post(url, { code });
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
  // logout
  logout: async (userId: number, jwt: string): Promise<void> => {
    try {
      const url = authPath(`/logout/${userId}`);
      await instance.put(url, null, {
        headers: {
          Authorization: `Bearer ${jwt}`,
        },
      });
    } catch (e) {
      if (e instanceof Error) {
        console.error(e.message);
      } else {
        console.error(e);
      }
    }
  },
  // 2차 인증 등록시 이메일 등록 + 코드 발송
  setSecondAuth: async (
    id: number,
    email: string,
    jwt: string,
  ): Promise<{ isOk: boolean } | null> => {
    try {
      const url = authPath(`/secondAuth/${id}`);
      const response = await instance.post(
        url,
        { email },
        {
          headers: {
            Authorization: `Bearer ${jwt}`,
          },
        },
      );
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

  // 2차 인증 등록 완료
  enrollSecondAuth: async (id: number, jwt: string): Promise<boolean> => {
    try {
      const url = authPath(`/secondAuthEnroll/${id}`);
      await instance.get(url, {
        headers: {
          Authorization: `Bearer ${jwt}`,
        },
      });
      return true;
    } catch (e) {
      if (e instanceof Error) {
        console.error(e.message);
      } else {
        console.error(e);
      }
      return false;
    }
  },

  // 2차 인증 코드 발송(수행)
  sendSecondAuthCode: async (id: number, jwt: string): Promise<{ isOk: boolean } | null> => {
    try {
      const url = authPath(`/secondAuth/${id}`);
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

  // 2차 인증 해제
  unsetSecondAuth: async (id: number, jwt: string): Promise<boolean> => {
    try {
      const url = authPath(`/secondAuth/${id}`);
      await instance.delete(url, {
        headers: {
          Authorization: `Bearer ${jwt}`,
        },
      });
      return true;
    } catch (e) {
      if (e instanceof Error) {
        console.error(e.message);
      } else {
        console.error(e);
      }
      return false;
    }
  },

  // 2차 인증 코드 체크(검증)
  checkSecondAuthCode: async (
    id: number,
    code: number,
    jwt: string,
  ): Promise<{ isOk: boolean; jwt: string } | null> => {
    try {
      const url = authPath(`/secondAuthVerify/${id}?code=${code}`);
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

  // 닉네임 중복 체크
  checkNickname: async (
    nickname: string,
    jwt: string,
  ): Promise<{ isDuplicate: boolean } | null> => {
    try {
      const url = authPath(`/isDuplicateNickname`);
      const response = await instance.post(
        url,
        { nickname },
        {
          headers: {
            Authorization: `Bearer ${jwt}`,
          },
        },
      );
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
  // 정상 JWT인지 검수
  checkNormJWT: async (jwt: string): Promise<string | boolean> => {
    try {
      const url = authPath(`/testJWT`);
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
      return false;
    }
  },
};
