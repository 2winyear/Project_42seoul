import styled from '@emotion/styled';
import React from 'react';
import Modal from '.';

const CancelMatchModal: React.FC = () => {
  return (
    <Modal width={400} height={200}>
      <ModalWrap>
        <ModalMsg>매칭이 취소되었습니다.</ModalMsg>
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

export default CancelMatchModal;
