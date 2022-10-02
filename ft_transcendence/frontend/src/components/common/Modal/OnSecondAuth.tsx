import React, { useState, useContext } from 'react';
import styled from '@emotion/styled';
import Button from '../Button';
import Modal from '.';
import { authAPI } from '../../../API';
import { AllContext } from '../../../store';
import { UPDATE_USER } from '../../../utils/interface';

const reg = new RegExp(
  /^[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*\.[a-zA-Z]{2,3}$/,
);
const OnSecondAuth: React.FC = () => {
  const { user, setUser } = useContext(AllContext).userData;
  const { jwt } = useContext(AllContext).jwtData;
  const { setModal } = useContext(AllContext).modalData;
  const [errMsg, setErrMsg] = useState<string>('');

  const [emailMsg, setEmailMsg] = useState<string>('');
  const [email, setEmail] = useState<string>('');

  const [authMsg, setAuthMsg] = useState<string>('');
  const [authCode, setAuth] = useState<string>('');

  const [activeEmail, setActiveEmail] = useState<boolean>(false);
  const [activeCode, setActiveCode] = useState<boolean>(true);

  const validEmailChecker = async () => {
    setEmailMsg('...');
    if (!reg.test(email)) {
      setEmailMsg('유효한 이메일이 아닙니다.');
    } else if (!user) {
      setEmailMsg('유저 정보가 없습니다.');
    } else {
      const res = await authAPI.setSecondAuth(user.userId, email, jwt);

      if (res && !res.isOk) {
        setEmailMsg('인증 코드가 전송에 실패하였습니다.');
      } else {
        setEmailMsg('인증 코드가 전송되었습니다.');
        setActiveCode(false);
      }
    }
  };

  const EmailhandleEnter = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (e.key === 'Enter') {
      validEmailChecker();
    }
  };

  const checkAuthCode = async () => {
    if (user) {
      if (authCode) {
        const res = await authAPI.checkSecondAuthCode(user.userId, Number(authCode), jwt);
        if (res && res.isOk) {
          setAuthMsg('인증에 성공하였습니다.');
          setActiveEmail(true);
        } else setAuthMsg('코드가 일치하지 않습니다.');
      } else setAuthMsg('코드를 입력해주세요.');
    } else setAuthMsg('새로고침 후 다시 진행해주세요.'); // user 정보 만료
  };

  const AuthhandleEnter = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (e.key === 'Enter') {
      checkAuthCode();
    }
  };

  const activeSecondAuth = async () => {
    if (activeEmail === true && user) {
      const res = await authAPI.enrollSecondAuth(user.userId, jwt);
      if (res) {
        setErrMsg('활성화에 성공하였습니다.');
        setUser(UPDATE_USER, { ...user, isSecondAuthOn: true });
        setModal(null);
      } else {
        setErrMsg('활성화에 실패했습니다.');
      }
    }
  };

  return (
    <Modal width={570} height={510} title={'2차 인증 활성화'}>
      <MainBlock>
        <EmailText>2차인증을 설정할 이메일을 입력해주세요.</EmailText>
        <InputEmail
          onChange={event => {
            setEmail(event.target.value);
            setEmailMsg('');
          }}
          spellCheck={false}
          value={email}
          onKeyPress={EmailhandleEnter}
          disabled={activeEmail}
        />
        <ErrEmail>{emailMsg}</ErrEmail>
        <Button
          color="white"
          text="인증코드 발송"
          width={150}
          height={40}
          onClick={validEmailChecker}
        />
        <AuthBlock>
          <AuthText>인증 코드 : </AuthText>
          <InputAuthCode
            onChange={event => {
              setAuth(event.target.value);
              setAuthMsg('');
            }}
            spellCheck={false}
            value={authCode}
            onKeyPress={AuthhandleEnter}
            disabled={activeCode}
          />
          <Button color="white" text="확인" width={70} height={35} onClick={checkAuthCode} />
        </AuthBlock>
        <ErrAuth>{authMsg}</ErrAuth>
        <Button
          color="gradient"
          text="활성화"
          width={200}
          height={40}
          onClick={activeSecondAuth}
          disabled={activeEmail === false ? true : false}
        />
        <ErrAuth>{errMsg}</ErrAuth>
      </MainBlock>
    </Modal>
  );
};

//Main Block
const MainBlock = styled.div`
  padding: 13px;
  width: 100%;

  & button {
    border-radius: 5px;
    &:first-of-type {
      margin-top: 10px;
    }
  }
`;
//============================================

//EmailSection
const EmailText = styled.span`
  display: block;
  width: 370px;
  text-align: center;
  margin: 0 auto;
  margin-top: 40px;
  font-size: 20px;
  font-weight: 400;
`;

const InputEmail = styled.input`
  display: block;
  margin: 0 auto;
  margin-top: 30px;
  width: 300px;
  text-align: center;
  border: none;
  outline: none;
  border-bottom: 1px solid;
  &:disabled {
    background-color: ${({ theme }) => theme.colors.grey};
  }
`;

const ErrEmail = styled.span`
  display: block;
  width: 370px;
  height: 14px;
  text-align: center;
  margin: 0 auto;
  margin-top: 15px;
  font-size: 14px;
  font-weight: 400;
  color: #ff6363;
`;
//============================================

//AuthSection
const AuthBlock = styled.div`
  width: 370px;
  height: 45px;
  margin: 0 auto;
  margin-top: 50px;
  & button {
    display: inline-block;
    margin-left: 10px;
  }
`;

const AuthText = styled.span`
  width: 90px;
  text-align: center;
  font-size: 20px;
  font-weight: 400;
`;

const InputAuthCode = styled.input`
  width: 180px;
  text-align: center;
  border: none;
  outline: none;
  border-bottom: 1px solid;
  &:disabled {
    background-color: ${({ theme }) => theme.colors.grey};
  }
`;

const ErrAuth = styled.span`
  display: block;
  width: 370px;
  height: 14px;
  text-align: center;
  margin: 0 auto;
  margin-top: 10px;
  margin-bottom: 10px;

  font-size: 14px;
  font-weight: 400;
  color: #ff6363;
`;
//============================================
export default OnSecondAuth;
