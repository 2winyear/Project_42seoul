import React from 'react';
import styled from '@emotion/styled';
import { IChatRooms, IGameRooms, CHAT } from '../../utils/interface';
import ChatRooms from './ChatRooms';
import GameRooms from './GameRooms';
interface RoomListProps {
  list: IChatRooms[] | IGameRooms[] | [];
  type: string;
}

const RoomList: React.FC<RoomListProps> = ({ list, type }) => {
  const listItems = list.map((li, index) => {
    return type === CHAT ? (
      <ChatRooms key={index} item={li as IChatRooms} />
    ) : (
      <GameRooms key={index} item={li as IGameRooms} />
    );
  });

  return (
    <>
      {list.length > 0 ? (
        <RoomListContainer>{listItems}</RoomListContainer>
      ) : (
        <EmptyRoomListWrap>
          <EmptyRoomList>암것도 없어유~!</EmptyRoomList>
        </EmptyRoomListWrap>
      )}
    </>
  );
};

const EmptyRoomListWrap = styled.div`
  display: flex;
  height: 100%;
  font-size: 15px;
`;
const EmptyRoomList = styled.p`
  margin: auto;
  font-size: 35px;
  color: ${props => props.theme.colors.main};
`;

const RoomListContainer = styled.ul`
  display: block;
  width: 100%;
  height: calc(100% - 60px);
  overflow: auto;
`;

export default RoomList;
