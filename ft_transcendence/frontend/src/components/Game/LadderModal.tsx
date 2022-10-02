import React, { useEffect, useContext } from 'react';
import styled from '@emotion/styled';
import Modal from '../common/Modal';
import Button from '../common/Button';
import { AllContext } from '../../store';
import { io, Socket } from 'socket.io-client'; // 아이오 연결하고.
import { useNavigate } from 'react-router-dom'; //네비

let socket: Socket;

const LadderModal: React.FC = () => {
  const { setModal } = useContext(AllContext).modalData;
  const navigate = useNavigate();
  const { user } = useContext(AllContext).userData;
  const { playingGameInfo, setPlayingGameInfo } = useContext(AllContext).playingGameInfo;

  useEffect(() => {
    // 소켓연결 하고
    socket = io(`${process.env.REACT_APP_BACK_API}/ws-game`, {
      transports: ['websocket'],
      multiplex: false,
      query: {
        userId: user?.userId,
        connectionType: 'ladderQueue',
      },
    });

    // 매치가 완료됐다고 서버한테 연락받으면
    socket.on('matchingGame', (roomId: number) => {
      setModal(null);
      if (user) {
        setPlayingGameInfo({
          ...playingGameInfo,
          gameRoomId: roomId,
          gameMode: 'normal',
          gameLadder: true,
        });
      }

      navigate(`/gameroom/${roomId}`); //GamePage.tsx
    });
    return () => {
      socket.off('matchingGame');
      socket.off('message');
      socket.disconnect();
    };
  }, []);
  return (
    <Modal width={400} height={200}>
      <ModalWrap>
        <LadderMsg>래더 게임 매칭중 입니다</LadderMsg>
        <CancelBtnWrap>
          <Button
            width={110}
            height={30}
            color="white"
            text="취소"
            onClick={() => {
              socket.disconnect();
              setModal(null);
            }}
          />
        </CancelBtnWrap>
      </ModalWrap>
    </Modal>
  );
};

const LadderMsg = styled.h3`
  font-size: 20px;
  font-weight: bold;
  text-align: center;
  display: block;
  margin-top: 30px;
`;

const ModalWrap = styled.div``;

const CancelBtnWrap = styled.div`
  margin-top: 30px;
  & button {
    font-size: 18px;
    border-radius: 5px;
  }
`;

export default LadderModal;
