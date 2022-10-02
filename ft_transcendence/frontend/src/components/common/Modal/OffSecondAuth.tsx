import React, { useContext } from 'react';
import styled from '@emotion/styled';
import Modal from '.';
import Button from '../Button';
import { AllContext } from '../../../store';
import { UPDATE_USER } from '../../../utils/interface';
import { authAPI } from '../../../API';

const OffSecondAuth: React.FC = () => {
  const { setModal } = useContext(AllContext).modalData;
  const { user, setUser } = useContext(AllContext).userData;
  const { jwt } = useContext(AllContext).jwtData;

  const offSecondAuth = async () => {
    if (user) {
      const res = await authAPI.unsetSecondAuth(user.userId, jwt);
      if (res) {
        setUser(UPDATE_USER, { ...user, isSecondAuthOn: false });
        setModal(null);
      }
    }
  };

  return (
    <Modal width={400} height={180}>
      <OffMsg>정말 2차 인증을 해제 하시겠습니까?</OffMsg>
      <CancelBtnWrap>
        <Button width={110} height={30} color="white" text="취소" onClick={() => setModal(null)} />
        <Button width={110} height={30} color="main" text="확인" onClick={offSecondAuth} />
      </CancelBtnWrap>
    </Modal>
  );
};

const OffMsg = styled.h3`
  margin-top: 20px;
  font-size: 20px;
  font-weight: bold;
  text-align: center;
`;
const CancelBtnWrap = styled.div`
  margin: 30px 0;
  display: flex;
  justify-content: center;
  align-items: center;

  & button {
    margin: 0;
    margin-right: 10px;
  }
`;

export default OffSecondAuth;
