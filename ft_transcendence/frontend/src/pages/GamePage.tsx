import React, { useContext, useState, useEffect } from 'react';
import styled from '@emotion/styled';
import Header from '../components/Header';
import { GAME } from '../utils/interface'; //UPDATE_USER, PLAY
import { AllContext } from '../store';
import defaultProfile from '../assets/default-image.png';
import ProfileImage from '../components/common/ProfileImage';
import { io, Socket } from 'socket.io-client';
import GameStart from './GameStart';
import { useNavigate } from 'react-router-dom';
import LoadingPage from './LoadingPage';

// 내가 쓸 변수 && 받아올 데이터 담긴변수 정의
interface GameInfoDto {
  nicknameOne: string;
  avatarOne: string;
  winCountOne: number;
  loseCountOne: number;
  ladderLevelOne: number;
  nicknameTwo: string;
  avatarTwo: string;
  winCountTwo: number;
  loseCountTwo: number;
  ladderLevelTwo: number;
  nickname: string;
  avatar: string;
  winCount: number;
  loseCount: number;
  ladderWinCount: number;
  ladderLoseCount: number;
  ladderLevel: number;
  group: string;
}

const GamePage: React.FC = () => {
  let socket: Socket;
  const navigate = useNavigate();
  const [gameStart, setGameStart] = useState(false);
  const { user } = useContext(AllContext).userData; // setUser
  const { playingGameInfo, setPlayingGameInfo } = useContext(AllContext).playingGameInfo;
  const [watchState, setWatchState] = useState(playingGameInfo.gameState);
  const [count, setCount] = useState<number>();
  const [info, setInfo] = useState<GameInfoDto>({
    nicknameOne: '',
    avatarOne: '',
    winCountOne: 0,
    loseCountOne: 0,
    ladderLevelOne: 0,
    nicknameTwo: '',
    avatarTwo: '',
    winCountTwo: 0,
    loseCountTwo: 0,
    ladderLevelTwo: 0,
    nickname: '',
    avatar: '',
    winCount: 0,
    loseCount: 0,
    ladderWinCount: 0,
    ladderLoseCount: 0,
    ladderLevel: 0,
    group: '',
  });

  const settingMatchData = (p1: GameInfoDto, p2: GameInfoDto) => {
    if (p1 && p2 && user) {
      if (user.nickname === p1.nickname)
        setPlayingGameInfo({
          ...playingGameInfo,
          player: 'p1',
          oneNickname: p1.nickname,
          twoNickname: p2.nickname,
        });
      else if (user.nickname === p2.nickname)
        setPlayingGameInfo({
          ...playingGameInfo,
          player: 'p2',
          oneNickname: p1.nickname,
          twoNickname: p2.nickname,
        });
      else {
        setPlayingGameInfo({
          ...playingGameInfo,
          player: 'g1',
          oneNickname: p1.nickname,
          twoNickname: p2.nickname,
        });
      }
    }
  };

  const socketConnect = (roomid: number) => {
    socket = io(`${process.env.REACT_APP_BACK_API}/ws-game`, {
      transports: ['websocket'],
      multiplex: false,
      query: {
        userId: user && user.userId,
        roomId: roomid && roomid,
        connectionType: playingGameInfo.gameLadder ? 'ladderGame' : 'normalGame',
      },
    });

    socket.on('message', () => {
      // setUser(UPDATE_USER, { ...user, socket: socket });
      if (user) user.socket = socket;
    });
  };

  const socketDisonnect = (socket: Socket) => {
    if (socket) {
      socket.off('playerDisconnected');
      socket.off('gameDestroyed');
      socket.off('gameStartCount');
      socket.off('matchData');
      socket.disconnect();
    }
  };

  const scoreBarStyle = (bar: HTMLElement | null, win: number, lose: number) => {
    if (bar) bar.style.width = `${(win / (win + lose)) * 100}%`;
  };

  useEffect(() => {
    const win: HTMLElement | null = document.getElementById('win');
    const win2: HTMLElement | null = document.getElementById('win2');
    const roomId: number = playingGameInfo.gameRoomId;

    if (user && playingGameInfo) {
      socketConnect(roomId);

      /*
       * 서버에게 매치데이터를 받을 준비가 되었다고 알립니다.
       * roomid를 넘겨받은 서버는, matchData를 게임방의 유저들에게 보내줍니다.
       */
      socket.emit('onMatchingScreen', roomId);

      /*
       * 래더게임방일 경우를 확인합니다.
       * playerDisconnected 로 유저 연결상태를 확인합니다.
       * 표시해줄 매치데이타를 래더에 맞게 가공하고 저장합니다.
       */
      if (playingGameInfo.gameLadder === true) {
        playingGameInfo.gameLadder = false;
        socket.on('matchData', (p1: GameInfoDto, p2: GameInfoDto) => {
          if (!p1) {
            socketDisonnect(socket);
            navigate('/game');
          }
          if (p1 && p2) {
            setInfo(info => {
              return {
                ...info,
                nicknameOne: p1.nickname,
                avatarOne: p1.avatar,
                winCountOne: p1.ladderWinCount,
                loseCountOne: p1.ladderLoseCount,
                ladderLevelOne: p1.ladderLevel,
                nicknameTwo: p2.nickname,
                avatarTwo: p2.avatar,
                winCountTwo: p2.ladderWinCount,
                loseCountTwo: p2.ladderLoseCount,
                ladderLevelTwo: p2.ladderLevel,
              };
            });
            scoreBarStyle(win, p1.ladderWinCount, p1.ladderLoseCount);
            scoreBarStyle(win2, p2.ladderWinCount, p2.ladderLoseCount);
            settingMatchData(p1, p2);
          }
        });
      } else {
        /*
         * 이름 : matchData, p1, p2(대전유저들의 프로필정보를 받아옵니다)
         * 특징 : p2가 게임시작전에 나갈경우, p1과 p2에 모두 null이 담긴 연락이 옵니다.
         * 사용 : 래더의 경우는 무조건 폭파되는 조건으로 활용하고, 일반게임의 경우 플레이어2의 상태를 갱신합니다.
         */
        socket.on('matchData', (p1: GameInfoDto, p2: GameInfoDto) => {
          /*
           * 화살표함수와 return을 활용하여, 직전데이터를 받아 갱신합니다.
           * 일반적인 useState함수로 처리할 경우에는, info의 데이터가 최신이 아닙니다(비동기)
           * 전적바 디폴트로 수정해줍니다.
           */
          if (!p1 && !p2) {
            setCount(undefined);
            setInfo(info => {
              return {
                ...info,
                nicknameTwo: '곧 들어와요!',
                avatarTwo: '',
                winCountTwo: 0,
                loseCountTwo: 0,
                ladderLevelTwo: 0,
              };
            });
            if (win2) win2.style.width = `50%`;
          } else {
            setInfo({
              ...info,
              nicknameOne: p1.nickname,
              avatarOne: p1.avatar,
              winCountOne: p1.winCount,
              loseCountOne: p1.loseCount,
              ladderLevelOne: p1.ladderLevel,
              nicknameTwo: p2 ? p2.nickname : info.nicknameTwo,
              avatarTwo: p2 ? p2.avatar : info.avatarTwo,
              winCountTwo: p2 ? p2.winCount : info.winCountTwo,
              loseCountTwo: p2 ? p2.loseCount : info.loseCountTwo,
              ladderLevelTwo: p2 ? p2.ladderLevel : info.ladderLevelTwo,
            });
            if (p1) scoreBarStyle(win, p1.winCount, p1.loseCount);
            if (p2) scoreBarStyle(win2, p2.winCount, p2.loseCount);
            settingMatchData(p1, p2);
          }
        });
      }
      /*
       * 이름 : gameDestroyed, ()
       * 특징 : 방에 폭파조건에 부합하면 발생됩니다.
       *       일반게임 시작전, 방장이 나가기 버튼을 누른것을 감지합니다.
       * 사용 : 방폭파를 위해 남아있는 유저들을 정리합니다.
       */
      socket.on('gameDestroyed', () => {
        socketDisonnect(socket);
        navigate('/game');
      });
      /*
       * 이름 : gameStartCount, data(서버에서 계산한 카운트다운 넘버)
       * 특징 : 게임시작전 5초를 대기하며, 서버로부터 넘버를 받습니다.
       * 사용 : 보내온 카운트다운 넘버가  0될때, 게임을 시작합니다.
       */
      socket.on('gameStartCount', (data: number) => {
        setCount(data);
        if (data == 0) {
          setGameStart(true);
          // if (playingGameInfo.player !== 'p1' && playingGameInfo.player !== 'p2')
          setWatchState(false);
        }

        /*
         * 이름 : playerDisconnected, data(디스커넥트 유저 상세정보)
         * 특징 : 새로고침으로 한 유저의 소켓연결이 끊어지면, 발생합니다.
         *       버튼으로 나가는경우엔, gameDestroyed가 처리합니다.
         * 사용 : 방장의 연결해제 여부를 확인하고 남은 유저들을 정리합니다.
         *       받아오는 데이터가 수정될 예정입니다.
         */
        socket.on('playerDisconnected', (data: GameInfoDto) => {
          if (data.group === '1p') {
            socketDisonnect(socket);
            navigate('/game');
          }
        });
      });
    } else {
      socketDisonnect(socket);
      navigate('/game');
    }
    return () => {
      socketDisonnect(socket);
      navigate('/game');
    };
  }, [user]);
  return !user || (watchState && playingGameInfo.player === 'g1') ? (
    <LoadingPage />
  ) : (
    <Background>
      <GameRoomContainer>
        <Header type={GAME} />
        {gameStart === false ? (
          <GameRoomBody>
            <GameArea>
              <InfoArea>
                <UserInfo>
                  <PictureBlock>
                    <ProfileImage
                      src={info.avatarOne ? info.avatarOne : defaultProfile}
                      size={150}
                    />
                  </PictureBlock>
                  <span>{`${info.nicknameOne}`}</span>
                  <span>{`Lv. ${info.ladderLevelOne}`}</span>
                  <Bar>
                    <Win id="win">{info.winCountOne}</Win>
                    <Lose id="los">{info.loseCountOne}</Lose>
                  </Bar>
                </UserInfo>
                <Count>{count ? count : 'vs'}</Count>
                <UserInfo>
                  <PictureBlock>
                    <ProfileImage
                      src={info.avatarTwo ? info.avatarTwo : defaultProfile}
                      size={150}
                    />
                  </PictureBlock>
                  <span>{`${info.nicknameTwo}`}</span>
                  <span>{`Lv. ${info.ladderLevelTwo}`}</span>
                  <Bar>
                    <Win id="win2">{info.winCountTwo}</Win>
                    <Lose id="los">{info.loseCountTwo}</Lose>
                  </Bar>
                </UserInfo>
              </InfoArea>
              <Message>게임이 곧 시작됩니다</Message>
            </GameArea>
          </GameRoomBody>
        ) : (
          <GameStart />
        )}
      </GameRoomContainer>
    </Background>
  );
};

const PictureBlock = styled.div``;
const Bar = styled.div`
  position: relative;
  width: 210px;
  height: 26px;
  background: #ff6363;
  border-radius: 13px;
  /* overflow: hidden; */
`;

const Win = styled.div`
  width: 50%;
  height: 26px;
  background: #87b7ff;
  border-radius: 13px 0px 0px 13px;
  color: white;
  font-size: 14px;
  padding: 5px;
`;

const Lose = styled.div`
  position: absolute;
  top: 5px;
  right: 10px;
  height: 26px;
  color: white;
  font-size: 14px;
`;

const Message = styled.p`
  display: flex;
  justify-content: space-around;
  font-style: normal;
  font-family: 'Roboto';
  color: #ffd12e;
  //font-weight: 400;
  font-size: 40px;
  line-height: 64px;
  background-color: none;
`;

const InfoArea = styled.div`
  display: flex;
  align-items: center;
  justify-content: space-around;
  margin-top: 40px;
  width: 1000px;
  height: 500px;
`;

const Count = styled.p`
  font-style: normal;
  font-family: 'Roboto';
  color: white;
  display: flex;
  text-align: center;
  justify-content: center;
  font-size: 150px;
  width: 150px;
  line-height: 150px;
  background-color: none;
`;

const UserInfo = styled.div`
  display: flex;
  flex-direction: column;
  font-size: 30px;
  align-items: center;
  justify-content: space-around;
  width: 260px;
  height: 360px;
  //background-color: #f9f2ed;
  background-color: white;
  border-radius: 20px;
`;

const Background = styled.div`
  width: 100%;
  height: 100vh;
  background-color: ${({ theme }) => theme.colors.main};
  overflow-y: auto;
`;
const GameRoomContainer = styled.div`
  width: 1000px;
  margin: 0 auto;
  padding-bottom: 20px;
`;
const GameRoomBody = styled.div`
  display: flex;
  min-height: 700px;
  height: calc(100vh - 160px);
`;
const GameArea = styled.div`
  display: flex;
  flex-direction: column;

  width: 1000px;
  height: 700px;
  /* background-color: #f9f2ed; */
  background-color: black;
  border-radius: 20px;
`;

export default GamePage;
