import React, { useContext, useEffect, useState } from 'react';
import styled from '@emotion/styled';
import Modal from '.';
import Button from '../Button';
import { AllContext } from '../../../store';
import { io, Socket } from 'socket.io-client';
import { useNavigate } from 'react-router-dom';
import { usersAPI } from '../../../API';
import { CANCEL_MATCH_MODAL, IUserData } from '../../../utils/interface';

let socket: Socket;
/**
 * 대전 신청이 온 모달
 * @param matchUserId 대전 신청한 유저 id
 * @returns
 */
const FightReqModal: React.FC<{ matchUserId: number }> = ({ matchUserId }) => {
  const { setModal } = useContext(AllContext).modalData;
  const { user } = useContext(AllContext).userData;
  const [matchUser, setMatchUser] = useState<IUserData | null>(null);
  const navigate = useNavigate();
  // junselee 테스트
  const { playingGameInfo, setPlayingGameInfo } = useContext(AllContext).playingGameInfo;

  const acceptFight = () => {
    if (socket && user) {
      // userId : 대전 신청 받은 유저, targetId: 대전 신청한 유저
      socket.emit('acceptChallenge');
      // socket.emit('confirmMatch', { targetId: user.userId, userId: matchUserId });
    }
  };

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

  const getMatchUser = async () => {
    if (user && matchUserId) {
      const data = await usersAPI.getUserProfile(user.userId, matchUserId, user.jwt);
      if (data) {
        setMatchUser(data);
      }
    }
  };

  useEffect(() => {
    getMatchUser();
    if (user) {
      socket = io(`${process.env.REACT_APP_BACK_API}/ws-game`, {
        transports: ['websocket'],
        multiplex: false,
        query: {
          userId: user.userId,
          targetId: matchUserId,
          isSender: false,
          connectionType: 'duel',
        },
      });
      // TODO: acceptChallenge 사용되는 상황 파악

      socket.on('acceptChallenge', (userId: number) => {
        console.log('acceptChallenge', userId);
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
      socket.on('challengeSeqDone', () => {
        setModal(CANCEL_MATCH_MODAL);
      });
      socket.on('challengeRejected', () => {
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
        <FightMsg>{matchUser ? matchUser.nickname : undefined} 님에게</FightMsg>
        <FightMsg>대전 신청이 왔습니다.</FightMsg>
        <BtnBlock>
          <Button color="white" text="취소" width={110} height={30} onClick={cancelFight} />
          <Button color="gradient" text="수락" width={110} height={30} onClick={acceptFight} />
        </BtnBlock>
      </ModalWrap>
    </Modal>
  );
};

const FightMsg = styled.h3`
  font-size: 20px;
  font-weight: bold;
  line-height: 23px;
  text-align: center;
`;

const ModalWrap = styled.div`
  position: absolute;
  top: 55%;
  left: 50%;
  transform: translate(-50%, -50%);
`;

const BtnBlock = styled.div`
  margin-top: 20px;
  display: flex;
  justify-content: center;
  & button {
    font-size: 14px;
    border-radius: 5px;
    margin: 0;
    &:last-of-type {
      margin-left: 20px;
    }
  }
`;
export default FightReqModal;
