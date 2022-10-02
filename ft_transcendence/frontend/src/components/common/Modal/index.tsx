import React, { useContext, useEffect, useRef } from 'react';
import styled from '@emotion/styled';
import CloseImg from '../../../assets/close.png';
import { AllContext } from '../../../store';

interface ModalProps {
  width: number;
  height: number;
  children: React.ReactNode;
  title?: string;
}

const Modal: React.FC<ModalProps> = ({ width, height, title, children }) => {
  const { setModal } = useContext(AllContext).modalData;
  const backGroundRef = useRef<HTMLDivElement>(null);

  const onClickBackground = (e: React.MouseEvent<HTMLDivElement, MouseEvent>) => {
    // e.preventDefault(); // TODO: 이걸 사용해야하는 모달이 있는가?
    e.stopPropagation();
    if (e.target === backGroundRef.current) {
      setModal(null);
    }
  };

  const handleEscape = (e: React.KeyboardEvent<HTMLDivElement>) => {
    if (e.key === 'Escape') {
      setModal(null);
    }
  };

  useEffect(() => {
    backGroundRef.current?.focus();
  }, []);

  return (
    <ModalBackground
      onClick={onClickBackground}
      ref={backGroundRef}
      tabIndex={0}
      onKeyDown={handleEscape}
    >
      <ModalBox width={width} height={height}>
        {title && (
          <>
            <ModalHeader>
              <ModalTitle>{title}</ModalTitle>
              <ModalCloseBtn onClick={() => setModal(null)}>
                <CloseIcon src={CloseImg} alt="close" />
              </ModalCloseBtn>
            </ModalHeader>
          </>
        )}
        {children}
      </ModalBox>
    </ModalBackground>
  );
};

const ModalBackground = styled.div`
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  z-index: 2;
`;

const ModalBox = styled.div<{ width: number; height: number }>`
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  width: ${props => props.width}px;
  height: ${props => props.height}px;
  background-color: #fff;
  border-radius: 20px;
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.5);
  padding: 30px;
`;

const ModalHeader = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
  height: 25px;
`;
const ModalTitle = styled.h4`
  font-size: 20px;
  font-weight: bold;
  color: ${({ theme }) => theme.colors.main};
`;
const ModalCloseBtn = styled.button`
  width: 14px;
  height: 14px;
  border: none;
  background: none;
  cursor: pointer;
  padding: 0;
  transition: all 0.3s ease-in-out;
  &:hover {
    transform: scale(1.1);
  }
`;
const CloseIcon = styled.img`
  width: 100%;
  height: 100%;
  object-fit: contain;
`;

export default Modal;
