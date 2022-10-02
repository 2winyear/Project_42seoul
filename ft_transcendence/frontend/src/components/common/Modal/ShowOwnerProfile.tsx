import React, { useEffect, useState, useContext } from 'react';
import styled from '@emotion/styled';
import Button from '../Button';
import Modal from '.';
import defaultProfile from '../../../assets/default-image.png';
import {
  BAN_OR_KICK_MODAL,
  CANCEL_MATCH_MODAL,
  IChallengeResponse,
  CHECK_SCORE,
  ENTER_GAME_ROOM,
  FIGHT_RES_MODAL,
  IGameRooms,
  IUserData,
} from '../../../utils/interface';
import { AllContext } from '../../../store';
import { chatsAPI, gameAPI, usersAPI } from '../../../API';
import { useNavigate } from 'react-router-dom';
import ProfileImage from '../ProfileImage';

const ShowOwnerProfile: React.FC<{ roomId: number; userId: number }> = ({ roomId, userId }) => {
  const { setModal } = useContext(AllContext).modalData;
  const [target, setTarget] = useState<(IUserData & { isMuted: boolean; role: string }) | null>(
    null,
  );
  const { user } = useContext(AllContext).userData;
  const navigate = useNavigate();

  const [matchState, setMatchState] = useState<IChallengeResponse | null>(null);
  const [opponentData, setOpponentData] = useState<IGameRooms | null>(null);
  const { playingGameInfo, setPlayingGameInfo } = useContext(AllContext).playingGameInfo; // roomid기억하자.

  useEffect(() => {
    const getUserInfo = async () => {
      if (user && user.jwt) {
        const data = await chatsAPI.getUserProfileInChatRoom(roomId, user.userId, userId, user.jwt);
        const userTest = data?.userId;
        if (userTest) {
          const res = await gameAPI.dieDieMatch(user.userId, userTest, user.jwt);
          setMatchState(res);
          const res2 = await gameAPI.opponentState(userTest, user.jwt);
          if (res2 && res2.playerCount !== undefined) setOpponentData(res2);
        }
        if (data) {
          if (data.avatar) setTarget(data);
          else setTarget({ ...data, avatar: defaultProfile });
        }
      }
    };
    getUserInfo();
  }, []);

  const buttonName = () => {
    if (opponentData)
      switch (opponentData.playerCount) {
        case 0:
          return '게임 신청';
        case 1:
          return '참가 하기';
        default:
          return '관전 하기';
      }
    else if (
      matchState &&
      matchState.status === 'on' &&
      !matchState.blocked &&
      matchState.available === false
    )
      return '대기열 참가 중';
    else if (matchState && matchState.status === 'off' && matchState.available === false)
      return '오프 라인';
    else return '게임 신청';
  };

  const enterRoom = async () => {
    if (user && opponentData) {
      const res = await gameAPI.enterGameRoom(opponentData.gameId, user.userId, '', user.jwt);
      if (res && res.gameId !== undefined) {
        setPlayingGameInfo({
          ...playingGameInfo,
          gameRoomId: res.gameId,
          gameMode: res.gameMode,
          gameState: opponentData.isStart,
        });
        navigate(`/gameroom/${opponentData.gameId}`);
      }
    }
  };
  const handleEnterRoom = async () => {
    if (user && opponentData) {
      if (!opponentData.isPublic) {
        setModal(ENTER_GAME_ROOM, user.userId, opponentData.gameId);
      } else {
        await enterRoom();
      }
    }
  };

  const onApplyGame = async () => {
    if (target && user) {
      const res = await gameAPI.dieDieMatch(user.userId, target.userId, user.jwt);
      console.log(res);
      if (!res.available && res.blocked) {
        setModal(CANCEL_MATCH_MODAL);
        return;
      }
      const sat = buttonName();
      if (sat === '게임 신청' && res.available && res.status === 'on') {
        setModal(FIGHT_RES_MODAL, target.userId);
      } else if ((sat === '참가 하기' || sat === '관전 하기') && res.status === 'play') {
        handleEnterRoom();
      } else if (sat === '대기열 참가 중' || sat === '오프 라인') {
        return;
      } else {
        setModal(CANCEL_MATCH_MODAL);
      }
    }
  };
  const onSendDm = async () => {
    if (user && target) {
      const res = await chatsAPI.enterDmRoom(user.userId, target.userId, user.jwt);
      if (res && res.roomId) {
        setModal(null);
        navigate(`/chatroom/${res.roomId}`);
      }
    }
  };

  const onClickFriend = async () => {
    if (user && user.jwt && target) {
      if (target.isFriend === false) {
        await usersAPI.makeFriend(user.userId, target.userId, user.jwt);
      } else {
        await usersAPI.deleteFriend(user.userId, target.userId, user.jwt);
      }
      setTarget({
        ...target,
        isFriend: !target.isFriend,
      });
    }
  };

  const onClickBlock = async () => {
    if (user && user.jwt && target) {
      const res = await usersAPI.toggleBlockUser(user.userId, target.userId, user.jwt);
      setTarget({
        ...target,
        isFriend: false,
        isBlocked: !target.isBlocked,
      });
      if (res) {
        setModal(null);
      }
    }
  };

  // owner, manager
  const onToggleMute = async () => {
    if (target && user) {
      const res = await chatsAPI.setUpMuteUser(roomId, user.userId, target.userId, user.jwt);
      if (res) {
        setModal(null);
      }
    }
  };
  const handleKickOrBan = async () => {
    if (target) {
      setModal(BAN_OR_KICK_MODAL, target.userId, roomId);
    }
  };
  // just owner
  const onToggleRole = async () => {
    if (user && target) {
      const res = await chatsAPI.changeRoleInChatRoom(roomId, user.userId, target.userId, user.jwt);
      if (res) {
        setTarget({ ...target, role: res.role });
      }
    }
  };

  return (
    <>
      {target && (
        <Modal width={500} height={target.isBlocked === false ? 600 : 450} title={'프로필 보기'}>
          <MainBlock>
            <ProfileBlock>
              <PictureBlock>
                <ProfileImage src={target.avatar} size={100} />
              </PictureBlock>
              <UserInfo>
                <UserName>{target.nickname}</UserName>
                <UserLevel>lv.{target.ladderLevel}</UserLevel>
              </UserInfo>
            </ProfileBlock>

            <RecordText>전적/래더전적</RecordText>

            <RecordBlock>
              <Record>
                {target.winCount}승 {target.loseCount}패/{target.ladderWinCount}승{' '}
                {target.ladderLoseCount}패
              </Record>
              <RecordBtn>
                <Button
                  color="white"
                  text="전적 기록"
                  width={97}
                  height={30}
                  onClick={() => {
                    setModal(CHECK_SCORE, target.userId);
                  }}
                />
              </RecordBtn>
            </RecordBlock>
            {target.isBlocked === false ? (
              <OtherBtnBlock>
                <Button
                  color="gradient"
                  text={target.isFriend ? '친구 해제' : '친구 추가'}
                  width={200}
                  height={40}
                  onClick={onClickFriend}
                  disabled={target.isBlocked ? true : false}
                />
                <Button
                  color="gradient"
                  text={buttonName()}
                  width={200}
                  height={40}
                  onClick={onApplyGame}
                />
                <Button
                  color="gradient"
                  text="DM 보내기"
                  width={200}
                  height={40}
                  onClick={onSendDm}
                />
                <Button
                  color="white2"
                  text={target.isBlocked ? '차단해제' : '차단하기'}
                  width={200}
                  height={40}
                  onClick={onClickBlock}
                />
                <Button
                  color="white2"
                  text="강퇴 & 입장금지"
                  width={200}
                  height={40}
                  onClick={handleKickOrBan}
                />
                <Button
                  color="white2"
                  text="음소거"
                  width={200}
                  height={40}
                  onClick={onToggleMute}
                />
                <Button
                  color="gradient"
                  text={target.role === 'manager' ? '관리자 권한 해제' : '관리자 권한 주기'}
                  width={420}
                  height={40}
                  onClick={onToggleRole}
                />
              </OtherBtnBlock>
            ) : (
              <BanBtnBlock>
                <Button
                  color="white2"
                  text={target.isBlocked ? '차단해제' : '차단하기'}
                  width={415}
                  height={40}
                  onClick={onClickBlock}
                />
              </BanBtnBlock>
            )}
          </MainBlock>
        </Modal>
      )}
    </>
  );
};

// Main Block
const MainBlock = styled.div`
  padding: 13px;
  margin-top: 50px;
  width: 100%;
`;
//============================================

// Profile Section
const ProfileBlock = styled.div`
  height: 120px;
  display: flex;
`;
const UserInfo = styled.div``;

const PictureBlock = styled.div``;

const UserName = styled.span`
  display: block;
  font-size: 20px;

  margin-top: 25px;
  margin-left: 25px;
`;

const UserLevel = styled.span`
  display: block;
  font-size: 14px;

  margin-top: 5px;
  margin-left: 25px;
`;
//============================================

//Record Section
const RecordBlock = styled.div`
  display: flex;
  justify-content: space-between;
`;

const RecordText = styled.span`
  display: inline-block;
  font-size: 20px;
  line-height: 23px;

  margin-top: 71px;
`;

const Record = styled.span`
  display: inline-block;
  font-size: 16px;

  margin-top: 10px;
`;

const RecordBtn = styled.div`
  margin-top: 10px;
  & button {
    color: ${props => props.theme.colors.main};
    border-radius: 5px;
  }
`;

//============================================

//OtherBtnSection
const OtherBtnBlock = styled.div`
  display: grid;
  grid-template-columns: 1fr 1fr;
  grid-template-rows: 1fr 1fr 1fr 2fr;
  gap: 10px 20px;

  margin-top: 11px;
  & button {
    border-radius: 5px;
    &:last-of-type {
      grid-column: auto / span 2;
    }
  }
`;
const BanBtnBlock = styled.div`
  margin-top: 11px;
  & button {
    border-radius: 5px;
  }
`;
//============================================

export default ShowOwnerProfile;
