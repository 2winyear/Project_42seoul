import React, { useState, useEffect, useContext } from 'react';
import styled from '@emotion/styled';
import Header from '../components/Header';
import UserList from '../components/UserList';
import UserProfile from '../components/UserProfile';
import MessageList from '../components/Chat/MessageList';
import MessageInput from '../components/Chat/MessageInput';
import { CHAT, FIGHT_REQ_MODAL, IMessage } from '../utils/interface';
import { useParams } from 'react-router-dom';
import { AllContext } from '../store';
import { authAPI, chatsAPI } from '../API';
import backaway from '../assets/backaway.png';
import { useNavigate } from 'react-router-dom';
import io, { Socket } from 'socket.io-client';
// import 'antd/dist/antd.min.css';
// import { notification } from 'antd';
// import type { NotificationPlacement } from 'antd/es/notification';

// type NotificationType = 'success' | 'info' | 'warning' | 'error';
// // TODO: 상황별 노티가 나타나도록 분기 타줄 것
// const disconnectSocketNoti = (
//   type: NotificationType,
//   placement: NotificationPlacement,
//   msg: string,
// ) => {
//   notification[type]({
//     message: msg,
//     description: `원인 : ${msg}`,
//     placement,
//   });
// };

let socket: Socket;

const ChatPage: React.FC = () => {
  const [messages, setMessages] = useState<IMessage[] | []>([]);
  const { user } = useContext(AllContext).userData;
  const { setModal } = useContext(AllContext).modalData;
  const { roomId } = useParams();
  const [roomName, setRoomName] = useState<string>('');
  const [isDm, setRoomtype] = useState<boolean>(false);
  const navigate = useNavigate();

  const submitMessage = (message: string) => {
    if (user) {
      socket.emit('sendMessage', {
        userId: user.userId,
        roomId: roomId,
        message: message,
      });
    } else console.error('user가 없음');
  };

  useEffect(() => {
    if (user && roomId) {
      socket = io(`${process.env.REACT_APP_BACK_API}/ws-chat`, {
        transports: ['websocket'],
        multiplex: false,
        query: {
          userId: user.userId,
          roomId: roomId,
        },
      });
      if (socket) {
        socket.on('reloadChatHistory', (data: IMessage[]) => {
          setMessages(data);
        });
        socket.on('recieveMessage', (data: IMessage) => {
          setMessages(pre => [...pre, data]);
        });
        socket.on('disconnectSocket', () => {
          // 강퇴, 방폭파, 방 나가기 다 해당 socket event로 받아서 이동이 되기에 notification 지움
          navigate('/');
        });
        socket.on('updateChatRoomTitle', (data: string) => {
          setRoomName(data);
        });
        socket.on('challengeDuelFrom', (userId: number) => {
          setModal(FIGHT_REQ_MODAL, userId);
        });
      }
    }
    return () => {
      if (socket) {
        socket.off('reloadChatHistory');
        socket.off('recieveMessage');
        socket.off('updateChatRoomTitle');
        socket.off('disconnectSocket');
        socket.off('challengeDuelFrom');
        if (socket.connected) socket.disconnect();
      }
    };
  }, [roomId, user]);

  useEffect(() => {
    const checkJWT = async (): Promise<boolean> => {
      const check = window.localStorage.getItem('jwt');
      if (check) {
        const res = await authAPI.checkNormJWT(check);
        return res ? true : false;
      }
      return false;
    };
    const getRoomData = async () => {
      const result = await checkJWT();
      if (!result) navigate('/'); // logout
      if (roomId && user && user.jwt) {
        const res = await chatsAPI.getChatRoomStatus(+roomId, user.jwt);
        if (res) {
          setRoomName(res.title);
          if (res.isDm) setRoomtype(res.isDm);
        } else {
          console.log('강퇴');
          // disconnectSocketNoti('error', 'top', 'X');
          // TODO: 경고 모달 띄우기
          // TODO: API연결이라서 navigate가 disconnectSocket과 중복됨
          // navigate('/chat');
        }
      }
    };
    getRoomData();
  }, [user, roomId]);
  return (
    <Background>
      <ChatRoomContainer>
        <Header type={CHAT} />
        <ChatRoomBody>
          <ChatArea>
            <ChatTitle>
              <BackawayWrap
                onClick={() => {
                  navigate(-1);
                }}
              >
                <Backaway src={backaway} alt="backaway" />
              </BackawayWrap>
              {roomName}
            </ChatTitle>
            <MessageList messages={messages} />
            <MessageInput submitMessage={submitMessage} />
          </ChatArea>
          <ChatSideMenu>
            <UserList menuType={'INCHAT'} roomId={roomId} isDm={isDm} socket={socket} />
            <UserProfile />
          </ChatSideMenu>
        </ChatRoomBody>
      </ChatRoomContainer>
    </Background>
  );
};

const Background = styled.div`
  width: 100%;
  height: 100vh;
  background-color: ${({ theme }) => theme.colors.main};
  overflow-y: auto;
`;
const ChatRoomContainer = styled.div`
  width: 1000px;
  margin: 0 auto;
  padding-bottom: 20px;
`;
const ChatRoomBody = styled.div`
  display: flex;
  min-height: 700px;
  height: calc(100vh - 160px);
`;
const ChatArea = styled.div`
  width: 680px;
  background-color: white;
  border-radius: 20px;
  margin-right: 20px;
  padding: 20px;
`;
const ChatTitle = styled.h2`
  display: flex;
  font-size: 20px;
  font-weight: bold;
  margin: 0 10px 20px;
  align-items: center;
`;
const BackawayWrap = styled.div`
  margin-right: 22px;
  /* display: inline-block; */
`;
const Backaway = styled.img`
  width: 100%;
  height: 100%;
  object-fit: contain;
  user-select: none;
  cursor: pointer;
`;

const ChatSideMenu = styled.div``;

export default ChatPage;
