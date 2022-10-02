import React, { useContext, useEffect, useState } from 'react';
import styled from '@emotion/styled';
import Modal from '.';
import Button from '../Button';
import { AllContext } from '../../../store';
import { CANCEL_MATCH_MODAL, IUserData } from '../../../utils/interface';
import { io, Socket } from 'socket.io-client';
import { useNavigate } from 'react-router-dom';
import { usersAPI } from '../../../API';

let socket: Socket;
/**
 * 대전 신청한 사람한테 보이는 대기 모달
 * @param targetId : 대전 대상자의 id
 * @returns
 */
const FightResModal: React.FC<{ targetId: number }> = ({ targetId }) => {
  const { setModal } = useContext(AllContext).modalData;
  const { user } = useContext(AllContext).userData;
  const [targetInfo, setTargetInfo] = useState<IUserData | null>(null);
  const navigate = useNavigate();

  // junselee 테스트
  const { playingGameInfo, setPlayingGameInfo } = useContext(AllContext).playingGameInfo;

  const cancelFight = () => {
    // TODO: setModal로 바뀌니 disconnect로 안바꿔도 될것 같다
    if (socket && user) {
      // userId : 대전 신청 받은 유저, targetId: 대전 신청한 유저
      // socket.emit('cancelMatch', { targetId: user.userId, userId: matchUserId });
      // 백엔드에서 socket disconnect로 match cancel 인식
      socket.disconnect();
    }
    setModal(CANCEL_MATCH_MODAL);
  };

  const getTargetInfo = async () => {
    if (user && targetId) {
      const data = await usersAPI.getUserProfile(user.userId, targetId, user.jwt);
      if (data) {
        setTargetInfo(data);
      }
    }
  };

  useEffect(() => {
    getTargetInfo();
    if (user) {
      socket = io(`${process.env.REACT_APP_BACK_API}/ws-game`, {
        transports: ['websocket'],
        multiplex: false,
        query: { userId: user.userId, targetId: targetId, isSender: true, connectionType: 'duel' },
      });
      socket.on('challengeSeqDone', () => {
        setModal(CANCEL_MATCH_MODAL);
      });
      // TODO: acceptChallenge 사용되는 상황 파악
      socket.on('acceptChallenge', () => {
        // navigate(`/gameroom/${roomId}`);
        // junselee test : 신청측도 서버한테 알려줘야합니다.
        socket.emit('acceptChallenge');
      });
      socket.on('matchingGame', (roomId: number) => {
        // junselee 테스트
        if (user) {
          setPlayingGameInfo({
            ...playingGameInfo,
            gameRoomId: roomId,
            gameMode: 'normal',
            gameLadder: false,
          });
        }
        navigate(`/gameroom/${roomId}`);
      });
      socket.on('challengeRejected', (data: number) => {
        data;
        setModal(CANCEL_MATCH_MODAL);
      });
    }

    return () => {
      if (socket && socket.connected) socket.disconnect();
    };
  }, []);
  return (
    <Modal width={400} height={200}>
      <ModalWrap>
        <FightMsg>{targetInfo ? targetInfo.nickname : undefined}님의</FightMsg>
        <FightMsg>응답 대기중...</FightMsg>
        <CancelBtnWrap>
          <Button width={110} height={30} color="white" text="취소" onClick={cancelFight} />
        </CancelBtnWrap>
      </ModalWrap>
    </Modal>
  );
};

const FightMsg = styled.h3`
  font-size: 20px;
  font-weight: bold;
  text-align: center;
  line-height: 23px;
`;

const ModalWrap = styled.div`
  position: absolute;
  top: 55%;
  left: 50%;
  transform: translate(-50%, -50%);
`;
const CancelBtnWrap = styled.div`
  margin-top: 20px;
  & button {
    font-size: 14px;
    border-radius: 5px;
  }
`;

export default FightResModal;
