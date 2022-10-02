import styled from '@emotion/styled';
import React, { useContext, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import Modal from '.';
import { AllContext } from '../../../store';

const BanChatRoomModal: React.FC = () => {
  const { setModal } = useContext(AllContext).modalData;
  const navigate = useNavigate();

  useEffect(() => {
    const Timer = setTimeout(() => {
      setModal(null);
    }, 5000);

    return () => {
      clearTimeout(Timer);
      navigate('/chat');
    };
  }, []);

  return (
    <Modal width={400} height={200}>
      <ModalWrap>
        <ModalMsg> 강퇴당한 채팅방입니다.</ModalMsg>
      </ModalWrap>
    </Modal>
  );
};

const ModalWrap = styled.div`
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
`;
const ModalMsg = styled.p`
  font-size: 20px;
  color: ${props => props.theme.colors.red};
`;

export default BanChatRoomModal;
