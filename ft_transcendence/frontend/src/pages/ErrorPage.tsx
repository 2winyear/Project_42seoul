import React from 'react';
import styled from '@emotion/styled';

const ErrorPage: React.FC = () => {
  return (
    <Background>
      <ErrorMessage>잘못된 접근입니다.</ErrorMessage>
    </Background>
  );
};

const Background = styled.div`
  width: 100vw;
  height: 100vh;
  background-color: ${({ theme }) => theme.colors.main};
  position: relative;
`;

const ErrorMessage = styled.span`
  font-size: 40px;
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  display: block;
  text-align: center;
`;

export default ErrorPage;
