import React, { useState } from 'react';
import styled from '@emotion/styled';
import Button from '../Button';
import Modal from '.';
import { chatsAPI } from '../../../API';
import { useContext } from 'react';
import { AllContext } from '../../../store';

const SettingRoom: React.FC<{ roomId: number }> = ({ roomId }) => {
  const { user } = useContext(AllContext).userData;
  const { setModal } = useContext(AllContext).modalData;
  const [roomName, setRoomName] = useState<string>('');
  const [password, setPassword] = useState<string>('');
  const [errMsg, setErrMsg] = useState<string>('');
  const roomSettingValues = {
    MAXROOMNAMESIZE: 10,
    MAXPASSWORDSIZE: 10,
  };

  const onChangeInput = (e: React.ChangeEvent<HTMLInputElement>) => {
    if (errMsg.length) setErrMsg('');
    if (e.target.name === 'roomName') {
      if (e.target.value.length <= roomSettingValues.MAXROOMNAMESIZE) setRoomName(e.target.value);
      else setErrMsg(`방 제목은 최대 ${roomSettingValues.MAXROOMNAMESIZE} 글자 입니다.`);
    } else if (e.target.name === 'password') {
      if (e.target.value.length <= roomSettingValues.MAXPASSWORDSIZE)
        setPassword(e.target.value.trim());
      else setErrMsg(`방 비밀번호는 최대 ${roomSettingValues.MAXPASSWORDSIZE} 글자 입니다.`);
    }
  };

  const editRoomInfo = async () => {
    if (roomName.trim().length === 0) {
      setErrMsg('방 제목은 최소 한 글자 이상 입력해주세요.');
      return;
    }
    if (user) {
      const roomInfo = await chatsAPI.getChatRoomStatus(roomId, user.jwt);
      if (roomInfo && roomInfo.ownerId === user.userId) {
        await chatsAPI.setUpChatRoom(roomId, user.userId, roomName, password, user.jwt);
        setModal(null);
      }
    }
  };

  return (
    // TODO: 따로 게임방, 채팅방 설정으로 구분?
    <Modal width={570} height={300} title={'방 설정'}>
      <MainBlock>
        <TextGridBlock>
          <RoomNPwd>방 제목</RoomNPwd>
          <InputRoomName
            type="text"
            onChange={onChangeInput}
            value={roomName}
            name="roomName"
            spellCheck={false}
          />
          <RoomNPwd>비밀번호</RoomNPwd>
          <InputPwd type="password" name="password" onChange={onChangeInput} value={password} />
        </TextGridBlock>
        <ErrMsg>{errMsg}</ErrMsg>
        <BtnBlock>
          <Button color="gradient" text="설정" width={200} height={40} onClick={editRoomInfo} />
        </BtnBlock>
      </MainBlock>
    </Modal>
  );
};

// Main Block
const MainBlock = styled.div`
  padding: 13px;
  margin-top: 50px;
  width: 100%;
`;
//============================================

//InputSection
const TextGridBlock = styled.div`
  margin-left: 30px;
  margin-right: 40px;
  display: grid;
  grid-template-columns: 1fr 1fr;
  grid-template-rows: 1fr 1fr;
  gap: 15px 10px;
`;

const RoomNPwd = styled.span`
  width: 75px;
  font-size: 20px;
  font-weight: 400;
  text-align: center;
`;

const InputRoomName = styled.input`
  width: 250px;
  border: none;
  outline: none;
  border-bottom: 1px solid;
  text-align: center;
`;

const InputPwd = styled(InputRoomName)`
  text-align: center;
  &[type='password'] {
  }
`;

const ErrMsg = styled.span`
  display: block;
  height: 16px;
  font-size: 14px;
  color: ${({ theme }) => theme.colors.red};
  text-align: center;
  margin: 20px 0 10px;
`;

//============================================

//BtnSection
const BtnBlock = styled.div`
  margin-top: 20px;
  & button {
    border-radius: 5px;
  }
`;
//============================================

export default SettingRoom;
