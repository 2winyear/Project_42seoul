import { instance } from './index';
import {
  IChatRooms,
  IRoomSetting,
  IGetUser,
  IChatDMRoom,
  IMessage,
  IChatRoomInfo,
  IUserData,
} from '../utils/interface';
const chatsPath = (path: string) => {
  return `/chats${path}`;
};

const chatsAPI = {
  // GET chats - getChatRooms
  getChatRoom: async (jwt: string): Promise<IChatRooms[] | []> => {
    try {
      const url = chatsPath('');
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
  // GET chats/users/{userid} - getJoinedChatRooms
  getJoinedChatRooms: async (userId: number, jwt: string): Promise<IChatRooms[] | []> => {
    try {
      const url = chatsPath(`/users/${userId}`);
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
  // POST chats/{userid} -  makeChatRoom
  makeChatRoom: async (
    userId: number,
    title: string,
    isDm: boolean,
    password: string | null,
    jwt: string,
  ): Promise<IChatRoomInfo | null> => {
    try {
      const url = chatsPath(`/${userId}`);
      const res = await instance.post(
        url,
        { title, isDm, password },
        {
          headers: { Authorization: `Bearer ${jwt}` },
        },
      );
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // GET chats/{roomId} - getChatRoomStatus
  getChatRoomStatus: async (roomId: number, jwt: string): Promise<IChatRoomInfo | null> => {
    try {
      const url = chatsPath(`/${roomId}`);
      const res = await instance.get(url, {
        headers: { Authorization: `Bearer ${jwt}` },
      });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // GET chats/{roomid}/participants - getUsersInChatRoom
  getUsersInChatRoom: async (roomId: number, jwt: string): Promise<IGetUser[] | []> => {
    try {
      const url = chatsPath(`/${roomId}/participants`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return [];
    }
  },
  // POST chats/{roomid}/users/{userId} - enterChatRoom
  enterChatRoom: async (
    roomId: number,
    userId: number,
    password: string,
    jwt: string,
  ): Promise<number> => {
    try {
      const url = chatsPath(`/${roomId}/users/${userId}`);
      const res = await instance.post(
        url,
        { password },
        {
          headers: { Authorization: `Bearer ${jwt}` },
        },
      );
      return res.data;
    } catch (e) {
      if (e instanceof Error) {
        console.error(e.message);
        if (e.message.includes('403')) return -403;
      } else console.error(e);
      return -1;
    }
  },
  // DELETE chats/{roomid}/users/{userId} -  leaveChatRoom
  leaveChatRoom: async (roomId: number, userId: number, jwt: string) => {
    try {
      const url = chatsPath(`/${roomId}/users/${userId}`);
      await instance.delete(url, { headers: { Authorization: `Bearer ${jwt}` } });
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
    }
  },
  // PUT chats/{roomid}/users/{ownerId} - setUpChatRoom
  setUpChatRoom: async (
    roomId: number,
    ownerId: number,
    title: string,
    password: string,
    jwt: string,
  ): Promise<IRoomSetting | null> => {
    try {
      const url = chatsPath(`/${roomId}/users/${ownerId}`);
      const res = await instance.put(
        url,
        { title, password },
        { headers: { Authorization: `Bearer ${jwt}` } },
      );
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // POST chats/{myId}/dmRooms - enterDmRoom
  enterDmRoom: async (
    myId: number,
    partnerId: number,
    jwt: string,
  ): Promise<IChatDMRoom | null> => {
    try {
      const url = chatsPath(`/${myId}/dmRooms?partnerId=${partnerId}`);
      const res = await instance.post(url, null, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // GET chats/{roomid}/chatContents/{userId} - getMsgHistoryInChatRoom
  getMsgHistoryInChatRoom: async (
    roomId: number,
    userId: number,
    jwt: string,
  ): Promise<IMessage[] | []> => {
    try {
      const url = chatsPath(`/${roomId}/chatContents/${userId}`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return [];
    }
  },
  // PUT chats/{roomid}/role_toggle - changeRoleInChatRoom
  changeRoleInChatRoom: async (
    roomId: number,
    callingUserId: number,
    targetUserId: number,
    jwt: string,
  ): Promise<{ role: string } | null> => {
    try {
      const url = chatsPath(
        `/${roomId}/roleToggle?callingUserId=${callingUserId}&targetUserId=${targetUserId}`,
      );
      const res = await instance.put(url, null, {
        headers: { Authorization: `Bearer ${jwt}` },
      });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
  // PUT chats/{roomid}/ban/{userId} - banUserInChatRoom
  banUserInChatRoom: async (
    roomId: number,
    userId: number,
    targetUserId: number,
    jwt: string,
  ): Promise<boolean> => {
    try {
      const url = chatsPath(`/${roomId}/ban/${userId}?targetUserId=${targetUserId}`);
      await instance.put(url, null, {
        headers: { Authorization: `Bearer ${jwt}` },
      });
      return true;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return false;
    }
  },
  // PUT chats/:roomId/kick/:userId
  kickUserInChatRoom: async (
    roomId: number,
    userId: number,
    targetUserId: number,
    jwt: string,
  ): Promise<boolean> => {
    try {
      const url = chatsPath(`/${roomId}/kick/${userId}?targetUserId=${targetUserId}`);
      await instance.put(url, null, {
        headers: { Authorization: `Bearer ${jwt}` },
      });
      return true;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return false;
    }
  },
  // PUT chats/{roomId}/users/{callingUserId}/muteToggle - setUpMuteUser
  setUpMuteUser: async (
    roomId: number,
    callingUserId: number,
    targetUserId: number,
    jwt: string,
  ): Promise<{ isMuted: boolean }> => {
    try {
      const url = chatsPath(
        `/${roomId}/users/${callingUserId}/muteToggle?targetUserId=${targetUserId}`,
      );
      const res = await instance.put(url, null, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data; // INFO: isMuted : boolean
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return { isMuted: false };
    }
  },
  // POST chats/{roomid}/users/{userId}/messages - enrollChat
  enrollChat: async (
    roomId: number,
    userId: number,
    chatLog: IMessage,
    jwt: string,
  ): Promise<boolean> => {
    try {
      const url = chatsPath(`/${roomId}/users/${userId}/messages`);
      await instance.post(url, { data: chatLog }, { headers: { Authorization: `Bearer ${jwt}` } });
      return true;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return false;
    }
  },
  // GET chats/{roomId}/participants/{myId} - getUserProfileInChatRoom
  // TODO: return interface refactoring
  getUserProfileInChatRoom: async (
    roomId: number,
    myId: number,
    targetId: number,
    jwt: string,
  ): Promise<(IUserData & { isMuted: boolean; role: string }) | null> => {
    try {
      const url = chatsPath(`/${roomId}/participants/${myId}?targetId=${targetId}`);
      const res = await instance.get(url, { headers: { Authorization: `Bearer ${jwt}` } });
      return res.data;
    } catch (e) {
      if (e instanceof Error) console.error(e.message);
      else console.error(e);
      return null;
    }
  },
};

export { chatsAPI };
