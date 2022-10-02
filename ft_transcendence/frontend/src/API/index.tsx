import axios from 'axios';
import { authAPI } from './auth';
import { usersAPI } from './users';
import { chatsAPI } from './chats';
import { gameAPI } from './game';
const url = process.env.REACT_APP_BACK_API;

export const instance = axios.create({
  baseURL: url,
});

/* NOTE: Default 양식

=========
import { IUser } from '../utils/interface';
import { instance } from './index';

const authPath = (path: string) => {
  return `/auth${path}`;
};

export const authAPI = {
  isSignedUp: async (body: { code: string }): Promise<IUser | null> => {
    try {
      const url = authPath(`/isSignedUp`);
      const response = await instance.post(url, body);
      return response.data;
    } catch (e: any) {
      console.log(e.message);
      return null;
    }
  },
 
};



*/

export { authAPI, usersAPI, chatsAPI, gameAPI };
