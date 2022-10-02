import React, { useEffect, useState, useContext } from 'react';
import styled from '@emotion/styled';
import Button from '../Button';
import Modal from '.';
import { AllContext } from '../../../store';
import { IGameRecord } from '../../../utils/interface';
import { usersAPI } from '../../../API';

const CheckScore: React.FC<{ userId: number }> = ({ userId }) => {
  const [recordList, setRecord] = useState<IGameRecord[] | []>([]);
  const { setModal } = useContext(AllContext).modalData;
  const { user } = useContext(AllContext).userData;

  useEffect(() => {
    const getUserInfo = async () => {
      if (user && user.jwt) {
        const data = await usersAPI.getUserGameRecords(userId, user.jwt);
        setRecord(data.reverse());
      }
    };
    getUserInfo();
  }, []);

  return (
    <Modal width={450} height={450} title={'전적 확인'}>
      <MainBlock>
        <>
          {recordList.length !== 0 ? (
            <RecordList>
              {recordList.map((record: IGameRecord, index: number) => (
                <RecordItem key={index} isWin={record.isWin}>
                  <RecordisLadder>{record.isLadder ? '래더 게임' : '일반 게임'}</RecordisLadder>
                  <RecordisWin>{record.isWin ? '승' : '패'}</RecordisWin>
                  <RecordNickName>{record.opponentNickname}</RecordNickName>
                </RecordItem>
              ))}
            </RecordList>
          ) : (
            <NonRecordText>전적이 존재하지 않습니다</NonRecordText>
          )}
        </>
        <Button
          color="gradient"
          text="확인"
          width={200}
          height={40}
          onClick={() => setModal(null)}
        />
      </MainBlock>
    </Modal>
  );
};

// Main Block
const MainBlock = styled.div`
  margin: 0 auto;
  padding: 13px;
  width: 340px;
  & Button {
    margin-top: 25px;
  }
`;

const RecordItem = styled.div<{ isWin: boolean }>`
  margin: 0 auto;
  margin-top: 5px;
  width: 100%;
  height: 60px;

  background-color: ${props => (props.isWin ? '#c5dcff' : '#FFC5C5')};

  display: grid;
  grid-template-columns: 93px 23px 163px;
  grid-template-rows: 1fr;
  gap: 10px;

  border-radius: 5px;

  & span {
    display: inline-block;
    font-size: 18px;
    font-weight: 400;
    line-height: 60px;
  }
`;

const RecordList = styled.ul`
  height: 260px;
  overflow: auto;
  overflow-y: auto;
`;

const RecordisLadder = styled.span`
  width: 100%;
  text-align: center;
`;
const RecordisWin = styled.span`
  width: 100%;
  text-align: left;
  color: #ffffff;
`;
const RecordNickName = styled.span`
  width: 90%;
  text-align: right;
`;

const NonRecordText = styled.span`
  margin-top: 60px;
  height: 200px;
  display: inline-block;
  font-size: 25px;
  width: 100%;
  color: ${({ theme }) => theme.colors.deepGrey};
  text-align: center;
`;

export default React.memo(CheckScore);
