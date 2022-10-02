import React, { useEffect, useContext, useState } from 'react';
import styled from '@emotion/styled';
import { AllContext } from '../store';
import { LOGIN, SET_NICKNAME, SECOND_AUTH } from '../utils/interface';
import { useNavigate, useSearchParams } from 'react-router-dom';
import { authAPI } from '../API';

const OauthPage: React.FC = () => {
  const { setUserStatus } = useContext(AllContext).userStatus;
  const { setUser } = useContext(AllContext).userData;
  const { setJwt } = useContext(AllContext).jwtData;
  const navigate = useNavigate();
  const [params] = useSearchParams();
  const code = params.get('code');
  const [dot, setDot] = useState('.');

  useEffect(() => {
    const getUser = async () => {
      if (code) {
        const res = await authAPI.isSignedUp(code);
        if (res) {
          setUser(LOGIN, {
            ...res,
            winCount: 0,
            loseCount: 0,
            ladderWinCount: 0,
            ladderLoseCount: 0,
            ladderLevel: 0,
            isSecondAuthOn: false,
            isFriend: false,
            isBlocked: false,
          });
          // NOTE: 임시로 LocalStorage에 jwt 저장
          window.localStorage.setItem('jwt', res.jwt);
          setJwt('SET_JWT', res.jwt); // 전역 jwt에 저장
          if (!res.nickname) {
            setUserStatus(SET_NICKNAME);
          } else if (res.isSecondAuthOn) {
            setUserStatus(SECOND_AUTH);
          } else {
            setUserStatus(LOGIN);
          }
          navigate('/');
        } else if (window.localStorage.getItem('jwt')) {
          window.localStorage.removeItem('jwt');
          navigate('/');
        }
      }
    };
    // NOTE: 한번에 두번 요청되는것을 막기 위해 설정
    const timer = setTimeout(() => {
      getUser();
      clearTimeout(timer);
    }, 100);

    return () => clearTimeout(timer);
  }, []);

  useEffect(() => {
    const timer = setInterval(() => {
      if (dot === '...') setDot('.');
      else setDot(dot + '.');
    }, 500);

    return () => clearInterval(timer);
  });

  return (
    <Loading>
      <LoadingMessage>Loading{dot}</LoadingMessage>
    </Loading>
  );
};

const Loading = styled.div`
  width: 100vw;
  height: 100vh;
  background-color: ${({ theme }) => theme.colors.main};
  position: relative;
`;

const LoadingMessage = styled.span`
  display: block;
  font-size: 50px;
  color: white;
  width: 100%;
  text-align: center;
  white-space: nowrap;
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
`;

export default OauthPage;
