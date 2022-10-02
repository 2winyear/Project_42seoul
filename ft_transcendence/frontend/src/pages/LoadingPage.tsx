import React, { useEffect, useState } from 'react';
import styled from '@emotion/styled';

const LoadingPage: React.FC = () => {
  const [dot, setDot] = useState('.');

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

export default LoadingPage;
