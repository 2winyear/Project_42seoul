import React, { useContext } from 'react';
import { ENTER_GAME_ROOM, IGameRooms } from '../../utils/interface';
import Button from '../common/Button';
import styled from '@emotion/styled';
import { useNavigate } from 'react-router-dom';
import { gameAPI } from '../../API';
import { AllContext } from '../../store';

interface GameRoomProps {
  item: IGameRooms;
}

const GameRooms: React.FC<GameRoomProps> = ({ item }) => {
  const navigate = useNavigate();
  const { setModal } = useContext(AllContext).modalData;
  const { user } = useContext(AllContext).userData;
  const { playingGameInfo, setPlayingGameInfo } = useContext(AllContext).playingGameInfo; // roomid기억하자.

  const enterRoom = async () => {
    if (user) {
      const res = await gameAPI.enterGameRoom(item.gameId, user.userId, '', user.jwt);
      //if (res !== -1) { 자료형 바껴서 이제 예는 안씀.
      if (res && res.gameId !== undefined) {
        // 세팅해줘야 게임플레이방에서 쓸수있음.
        setPlayingGameInfo({
          ...playingGameInfo,
          gameRoomId: res.gameId,
          gameMode: res.gameMode,
          gameState: item.isStart,
        }); // 그럼이제 전역으로 모드를 들고다닐수 있게 된거심.
        navigate(`/gameroom/${item.gameId}`);
      }
    }
  };

  const handleEnterRoom = async () => {
    if (user) {
      if (!item.isPublic) {
        setModal(ENTER_GAME_ROOM, user.userId, item.gameId);
      } else {
        await enterRoom();
      }
    }
  };

  return (
    <ListItem>
      <ListTitle>{item.roomTitle}</ListTitle>
      <ListStatus>
        <PrivateStat>{item.isPublic ? `공개` : `비공개`}</PrivateStat>
        <CountStat>{item.playerCount + '명'}</CountStat>
        <EnterBtnWrap>
          <Button
            width={50}
            height={30}
            color="gradient"
            text="입장"
            onClick={handleEnterRoom} // TODO: navigate(`game/${roomNumber}`); // game room
          />
        </EnterBtnWrap>
        <GameStat isGameStart={item.isStart}>{item.isStart ? `게임중` : `대기중`}</GameStat>
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
const GameStat = styled.span<{ isGameStart: boolean }>`
  display: inline-block;
  width: 40px;
  color: ${({ isGameStart, theme }) => (isGameStart ? theme.colors.main : theme.colors.deepGrey)};
  text-align: right;
  margin-left: 20px;
  user-select: none;
`;

export default React.memo(GameRooms);
