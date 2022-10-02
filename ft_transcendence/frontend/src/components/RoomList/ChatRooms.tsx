import React, { useContext } from 'react';
import { ENTER_CHAT_ROOM, IChatRooms, BAN_THIS_CHATROOM } from '../../utils/interface';
import Button from '../common/Button';
import styled from '@emotion/styled';
import { useNavigate } from 'react-router-dom';
import { AllContext } from '../../store';
import { chatsAPI } from '../../API';

interface ChatRoomProps {
  item: IChatRooms;
}

const ChatRooms: React.FC<ChatRoomProps> = ({ item }) => {
  const navigate = useNavigate();
  const { setModal } = useContext(AllContext).modalData;
  const { user } = useContext(AllContext).userData;

  const enterRoom = async () => {
    if (user) {
      const res = await chatsAPI.enterChatRoom(item.roomId, user.userId, '', user.jwt);
      if (res === -403) {
        setModal(BAN_THIS_CHATROOM);
      } else if (res !== -1) {
        navigate(`/chatroom/${item.roomId}`);
      }
    }
  };

  const handleEnterRoom = async () => {
    if (user) {
      if (!item.isPublic) {
        const participants = await chatsAPI.getUsersInChatRoom(item.roomId, user.jwt);
        const participant = await participants.filter(participant => {
          return participant.userId === user.userId;
        });
        if (participant.length) await enterRoom();
        else setModal(ENTER_CHAT_ROOM, user.userId, item.roomId);
      } else {
        await enterRoom();
      }
    }
  };

  return (
    <ListItem>
      <ListTitle>{item.title}</ListTitle>
      <ListStatus>
        <PrivateStat>{item.isPublic ? `공개` : `비공개`}</PrivateStat>
        <CountStat>{item.numberOfParticipants + '명'}</CountStat>
        <EnterBtnWrap>
          <Button
            width={50}
            height={30}
            color="gradient"
            text="입장"
            onClick={handleEnterRoom} // TODO: change /chat/{roomNumber}
          />
        </EnterBtnWrap>
      </ListStatus>
    </ListItem>
  );
};

const ListItem = styled.li`
  display: flex;
  align-items: center;
  justify-content: space-between;
  width: 100%;
  height: 50px;
  background: #ffffff;
  border: 1px solid ${({ theme }) => theme.colors.grey};
  border-radius: 10px;
  margin: 10px 0;
  padding: 15px 20px;
  font-size: 14px;

  &:hover {
    border: 2px solid ${({ theme }) => theme.colors.main};
  }
`;

const ListTitle = styled.h4`
  user-select: none;
`;
const ListStatus = styled.div`
  display: flex;
  align-items: center;
  justify-content: flex-end;
`;
const PrivateStat = styled.span`
  display: inline-block;
  width: 40px;
  margin-right: 10px;
  text-align: right;
  user-select: none;
`;
const CountStat = styled.span`
  display: inline-block;
  width: 40px;
  margin-right: 20px;
  text-align: right;
  user-select: none;
`;
const EnterBtnWrap = styled.div`
  button {
    border-radius: 5px;
  }
`;

export default React.memo(ChatRooms);
