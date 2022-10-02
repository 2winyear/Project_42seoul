import Modal from '.';
import React, { useContext, useEffect, useState } from 'react';
import styled from '@emotion/styled';
import Button from '../Button';
import { AllContext } from '../../../store';
import { chatsAPI, usersAPI } from '../../../API';
import defaultProfile from '../../../assets/default-image.png';
import { IUserData } from '../../../utils/interface';

const BanOrKickModal: React.FC<{ roomId: number; userId: number }> = ({ roomId, userId }) => {
  const { setModal } = useContext(AllContext).modalData;
  const [target, setTarget] = useState<IUserData | null>(null);
  const { user } = useContext(AllContext).userData;

  useEffect(() => {
    const getUserInfo = async () => {
      if (user && user.jwt) {
        const data = await usersAPI.getUserProfile(user.userId, userId, user.jwt);
        if (data) {
          data.avatar ? setTarget(data) : setTarget({ ...data, avatar: defaultProfile });
        }
      }
    };
    getUserInfo();
  }, []);

  const handleKick = async () => {
    if (user && target) {
      const res = await chatsAPI.kickUserInChatRoom(roomId, user.userId, target.userId, user.jwt);
      if (res) {
        setModal(null);
      }
    }
  };
  const handleBan = async () => {
    if (user && target) {
      const res = await chatsAPI.banUserInChatRoom(roomId, user.userId, target.userId, user.jwt);
      if (res) {
        setModal(null);
      }
    }
  };

  return (
    <>
      <Modal width={400} height={180}>
        <BanMsg>어떻게 하실래융?</BanMsg>
        <BanBtnWrap>
          <Button width={110} height={30} color="main" text="강퇴만" onClick={handleKick} />
          <Button width={110} height={30} color="main" text="10초 입장 금지" onClick={handleBan} />
        </BanBtnWrap>
      </Modal>
    </>
  );
};

const BanMsg = styled.div`
  margin-top: 20px;
  font-size: 20px;
  font-weight: bold;
  text-align: center;
`;
const BanBtnWrap = styled.div`
  margin: 30px 0;
  display: flex;
  justify-content: center;
  align-items: center;

  & button {
    margin: 0;
    margin-right: 10px;
  }
`;
export default BanOrKickModal;
