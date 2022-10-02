import React, { useEffect, useContext } from 'react';
import styled from '@emotion/styled';
import Button from '../common/Button';
import ProfileImage from '../common/ProfileImage';
import { AllContext } from '../../store';
import {
  CHECK_SCORE,
  EDIT_MY_PROFILE,
  OFF_SECOND_AUTH,
  ON_SECOND_AUTH,
  UPDATE_USER,
} from '../../utils/interface';
import { usersAPI } from '../../API';
import { useNavigate } from 'react-router-dom';

const ProfilePage: React.FC = () => {
  const { setModal } = useContext(AllContext).modalData;
  const { user, setUser } = useContext(AllContext).userData;
  const navigate = useNavigate();

  useEffect(() => {
    const getUserInfo = async () => {
      if (user) {
        if (user.jwt) {
          const data = await usersAPI.getLoginUserProfile(user.jwt);
          if (data && data.nickname) {
            setUser(UPDATE_USER, { ...data, jwt: user.jwt });
          }
        } else {
          navigate('/'); // logout
        }
      }
    };
    getUserInfo();
  }, []);

  return (
    <>
      {user && (
        <MainBlock>
          <MainText>내 프로필</MainText>

          <ProfileBlock>
            <PictureBlock>
              <ProfileImage src={user.avatar} size={100} />
            </PictureBlock>
            <UserInfo>
              <UserName>{user.nickname}</UserName>
              <UserLevel>lv.{user.ladderLevel}</UserLevel>
            </UserInfo>
          </ProfileBlock>

          <RecordText>전적/래더전적</RecordText>

          <RecordBlock>
            <Record>
              {user.winCount}승 {user.loseCount}패/{user.ladderWinCount}승 {user.ladderLoseCount}패
            </Record>
            <RecordBtn>
              <Button
                color="white2"
                text="전적 기록"
                width={97}
                height={30}
                onClick={() => {
                  setModal(CHECK_SCORE, user.userId);
                }}
              />
            </RecordBtn>
          </RecordBlock>

          <OtherBtnBlock>
            <Button
              color="gradient"
              text="프로필 변경"
              width={120}
              height={30}
              onClick={() => {
                setModal(EDIT_MY_PROFILE, user.userId);
              }}
            />
            <Button
              color="gradient"
              text={user.isSecondAuthOn ? '2차 인증 해제' : '2차 인증 활성화'}
              width={120}
              height={30}
              onClick={() => setModal(user.isSecondAuthOn ? OFF_SECOND_AUTH : ON_SECOND_AUTH)}
            />
          </OtherBtnBlock>
        </MainBlock>
      )}
    </>
  );
};

// Main Block
const MainBlock = styled.div`
  background-color: white;
  border-radius: 20px;
  width: 300px;
  height: 340px;
  padding: 20px 25px;
  font-style: normal;
  font-weight: 400;
`;

// MainText Section
const MainText = styled.h3`
  font-size: 20px;
  line-height: 29px;

  color: ${props => props.theme.colors.main};
`;
//============================================

// Profile Section
const ProfileBlock = styled.div`
  height: 120px;
  display: flex;
`;
const UserInfo = styled.div``;

const PictureBlock = styled.div`
  margin-top: 20px;
  margin-left: 15px;
`;

const UserName = styled.span`
  display: block;
  font-size: 16px;
  line-height: 23px;

  margin-top: 45px;
  margin-left: 10px;
`;

const UserLevel = styled.span`
  display: block;
  font-size: 14px;
  line-height: 16px;

  margin-top: 5px;
  margin-left: 10px;
`;
//============================================

//RecordText Section
const RecordText = styled.span`
  display: inline-block;
  font-size: 14px;
  line-height: 16px;

  margin-top: 50px;
`;
//============================================

//Record Section
const RecordBlock = styled.div`
  display: flex;
  justify-content: space-between;
`;

const Record = styled.span`
  display: inline-block;
  font-weight: 400px;
  font-size: 16px;

  text-align: center;
  margin-top: 15px;
`;

const RecordBtn = styled.div`
  margin-top: 10px;
  & button {
    border-radius: 5px;
  }
`;
//============================================

//OtherBtnSection
const OtherBtnBlock = styled.div`
  display: flex;
  margin-top: 10px;
  & button {
    border-radius: 5px;
    margin: 0;
    &:last-of-type {
      margin-left: 10px;
    }
  }
`;
//============================================

export default ProfilePage;
