import React, { useEffect, useState, useContext } from 'react';
import styled from '@emotion/styled';
import Button from '../common/Button';
import ChatList from '../RoomList';
import { CHAT, ChatRoomType, IChatRooms, MAKE_CHAT_ROOM, ALL, JOINED } from '../../utils/interface';
import { AllContext } from '../../store';
import { chatsAPI } from '../../API';
import { Socket } from 'socket.io-client';

const Chat: React.FC<{ socket: Socket }> = ({ socket }) => {
  const [chatList, setChatList] = useState<IChatRooms[]>([]);
  const [roomType, setRoomType] = useState<ChatRoomType>(ALL);
  const { setModal } = useContext(AllContext).modalData;
  const { user } = useContext(AllContext).userData;

  useEffect(() => {
    if (user && user.jwt) getAllChatList(user.jwt);
  }, []);

  useEffect(() => {
    if (socket) {
      if (roomType === ALL) {
        socket.on('updateChatRoomList', (data: IChatRooms[]) => {
          setChatList(data); // 전체 채팅방
        });
      } else if (roomType === JOINED) {
        socket.on('updateParticipnatingChatRoomList', (data: IChatRooms[]) => {
          setChatList(data); // 참여중인 채팅방 목록 전채
        });
      }
    }
    return () => {
      if (socket) {
        socket.off('updateChatRoomList');
        socket.off('updateParticipnatingChatRoomList');
        // socket.disconnect();
      }
    };
  }, [socket, roomType]);

  const onGetJoinedChatRooms = async () => {
    if (user && user.jwt) {
      const res = await chatsAPI.getJoinedChatRooms(user.userId, user.jwt);
      setChatList(res);
    } else console.error('not get user');
  };

  const getAllChatList = async (jwt: string) => {
    const data = await chatsAPI.getChatRoom(jwt);
    setChatList(data);
  };

  const handleRoomType = () => {
    if (roomType === ALL) {
      setRoomType(JOINED);
      onGetJoinedChatRooms();
    } else {
      setRoomType(ALL);
      if (user && user.jwt) getAllChatList(user.jwt);
    }
  };

  return (
    <>
      <EnteredRoomBtn>
        <Button
          width={120}
          height={40}
          color="white"
          text="방 만들기"
          onClick={() => setModal(MAKE_CHAT_ROOM)}
        />
        <Button
          width={160}
          height={40}
          color="gradient"
          text={roomType === ALL ? '참여중인 채팅방 보기' : '전체 방 보기'}
          onClick={handleRoomType}
        />
      </EnteredRoomBtn>
      {/* TODO: 채팅방이 하나도 없을 때 하나도 없다는걸 보여주는 info 컴포넌트 필요 */}
      <ChatList list={chatList} type={CHAT} />
    </>
  );
};

const EnteredRoomBtn = styled.div`
  display: flex;
  justify-content: flex-end;
  width: 100%;
  margin-bottom: 10px;
  button {
    margin: 0;
    font-size: 16px;
    /* font-weight: 500; */
    &:last-of-type {
      margin-left: 10px;
    }
  }
`;

export default Chat;
