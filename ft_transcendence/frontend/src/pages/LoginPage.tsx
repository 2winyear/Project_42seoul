import React from 'react';
import styled from '@emotion/styled';
import Button from '../components/common/Button';
import LogoImg from '../assets/logo.png';

const LoginPage: React.FC = () => {
  return (
    <LoginContainer>
      <LoginBox>
        <LogoWrap>
          <Logo src={LogoImg} alt="logo" />
        </LogoWrap>
        <Button
          width={200}
          height={50}
          color="white"
          text="42 Login"
          onClick={() => {
            if (process.env.REACT_APP_OAUTH_URL) {
              location.href = process.env.REACT_APP_OAUTH_URL;
            }
          }}
        />
      </LoginBox>
    </LoginContainer>
  );
};

const LoginContainer = styled.div`
  background-color: ${props => props.theme.colors.main};
  width: 100%;
  height: 100vh;
  overflow: hidden;
`;

const LoginBox = styled.div`
  width: 500px;
  height: 500px;
  background-color: white;
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  border-radius: 20px;
  box-shadow: 6px 6px 10px 5px rgba(0, 0, 0, 0.1);
  padding: 20px;
  box-sizing: border-box;
`;
const LogoWrap = styled.div`
  width: 90%;
  margin: 100px auto 150px;
`;
const Logo = styled.img`
  width: 100%;
  height: 100px;
  object-fit: contain;
`;

export default LoginPage;
