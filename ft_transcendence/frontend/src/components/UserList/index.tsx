import React, { useState, useEffect, useContext } from 'react';
import styled from '@emotion/styled';
import Button from '../common/Button';
import UserItem from './UserItem';
import { OFF, ActiveMenuType, IGetUser, UserRole } from '../../utils/interface';
import { AllContext } from '../../store';
import { chatsAPI, usersAPI } from '../../API';
import { Socket } from 'socket.io-client';

/*
 ** 제이슨서버에서 유저리스트를 받아와 정렬합니다.
 ** 리스트를 유저네임기준 오름차순으로 정렬 후, 상태 (로그인, 게임중) vs 로그아웃으로 비교하여 정렬합니다.
 ** 서클과 균형을 맞추기 위해서 넣었던 유저네임의 div가 필요없어져서 삭제함 <---- div에 바로 스타일주는거 고치라던 요청사항 수정중 2222
 ** 삼항연산으로 클릭을 확인하고, 또다시 친구관계를 확인하던 복잡한 구조를 개선함 <---- 요청사항 333
 ** useState 두개로 컬러값을 클릭마다 설정해주던거를, 버튼컬러에대한 삼항연산으로 개선했습니다.
 ** 전체유저버튼과 친구버튼의 클릭상태를 체크하는 useState 'click'의 이름을 직관적으로 수정하였습니다. 'allUser'
 ** props는 타입은 오브젝트로 수정.
 ** 타입명시할때 인터페이스사용한 적용 요청사항 111 <-- 인터페이스.tsx에 넣어서 가져다쓰자
 ** 충돌원인 /gamepage에 넣어논 태그삭제  요청사항 222
 */
// TODO:  userList type별로 출력하는 목록이 다르게 설정
interface UserListType {
  menuType: ActiveMenuType;
  roomId?: string;
  isDm?: boolean;
  socket?: Socket; // TODO: 라이브하게 유저리스트 갱신 시키기 위해 사용
}

const UserList: React.FC<UserListType> = ({ menuType, roomId, isDm, socket }) => {
  const { user } = useContext(AllContext).userData;
  const [activeMenu, setActiveMenu] = useState<ActiveMenuType>(menuType);
  const [userList, setUserList] = useState<IGetUser[] | []>([]);
  const [loginUserRole, setLoginUserRole] = useState<UserRole>('guest');

  const selectActiveMenu = async (menuType: ActiveMenuType): Promise<IGetUser[]> => {
    if (user) {
      switch (menuType) {
        case 'ALL':
          return await usersAPI.getAllUsersIdNickName(user.jwt);
        case 'FRIEND':
          return await usersAPI.getFriendList(user.userId, user.jwt);
        case 'INCHAT':
          return await chatsAPI.getUsersInChatRoom(+(roomId as string), user.jwt);
      }
    } else console.log('아무것도 없음');
    return [];
  };

  const sortedUserList = (data: IGetUser[]) => {
    data.sort((a: IGetUser, b: IGetUser) => {
      return a.nickname > b.nickname ? -1 : 1;
    });
    data.sort((a: IGetUser, b: IGetUser) => {
      b;
      return a.status !== OFF ? -1 : 1;
    });
    data.find(element => {
      if (user && element.userId === user.userId) {
        setLoginUserRole(element.role as UserRole);
      }
    });
    setUserList(data);
  };

  const getUserList = async () => {
    const data = await selectActiveMenu(activeMenu);
    sortedUserList(data);
  };

  useEffect(() => {
    if (socket) {
      if (activeMenu === 'ALL') {
        socket.on('updateUserList', (data: IGetUser[]) => {
          sortedUserList(data); // 전체 유저 목록
        });
      } else if (activeMenu === 'FRIEND') {
        socket.on('updateFriendList', (data: IGetUser[]) => {
          sortedUserList(data);
        });
      } else if (activeMenu === 'INCHAT') {
        socket.on('updateChatRoomParticipants', (data: IGetUser[]) => {
          sortedUserList(data);
        });
        socket.on('updateRole', (data: UserRole) => {
          setLoginUserRole(data);
        });
      }
    }
    return () => {
      if (socket) {
        // console.log('userList socket off');
        socket.off('updateUserList');
        socket.off('updateFriendList');
        socket.off('updateChatRoomParticipants');
        socket.off('updateRole');
      }
    };
  }, [socket, activeMenu]);

  useEffect(() => {
    if (user && user.jwt) getUserList();
  }, [activeMenu, user, roomId]);

  return (
    <>
      {user && (
        <ListBox>
          <ButtonBox>
            {menuType === 'INCHAT' ? (
              <>
                <Button
                  color={activeMenu === 'INCHAT' ? 'gradient' : 'white'}
                  text="채팅방유저"
                  width={120}
                  height={40}
                  onClick={() => {
                    setActiveMenu('INCHAT');
                  }}
                />
              </>
            ) : (
              <>
                <Button
                  color={activeMenu === 'ALL' ? 'gradient' : 'white'}
                  text="전체유저"
                  width={120}
                  height={40}
                  onClick={() => {
                    setActiveMenu('ALL');
                  }}
                />
              </>
            )}
            <Button
              color={activeMenu === 'FRIEND' ? 'gradient' : 'white'}
              text="친구"
              width={120}
              height={40}
              onClick={() => {
                setActiveMenu('FRIEND');
              }}
            />
          </ButtonBox>
          <UserContainer>
            <ul>
              {activeMenu !== 'ALL'
                ? userList.map(
                    (targetUser: IGetUser, index: number) =>
                      user.userId !== targetUser.userId && (
                        <UserItem
                          key={index}
                          loginUserRole={loginUserRole}
                          targetUser={targetUser}
                          menuType={activeMenu}
                          roomId={roomId}
                          isDm={isDm}
                        />
                      ),
                  )
                : userList.map(
                    (targetUser: IGetUser, index: number) =>
                      user.userId !== targetUser.userId && (
                        <UserItem key={index} targetUser={targetUser} menuType={activeMenu} />
                      ),
                  )}
            </ul>
          </UserContainer>
        </ListBox>
      )}
    </>
  );
};

/*
 ** 탭메뉴(전체유저, 친구)의 부모태그입니다.
 ** 전체유저 태그에 오른쪽마진으로 피그마와 비슷한 간격을 만들어주고, 두버튼의 폰트사이즈를 지정합니다.
 **
 */
const ButtonBox = styled.div`
  & :first-of-type {
    margin-right: 15px;
  }
  & button {
    font-size: 16px;
  }
  display: flex;
  justify-content: space-between;
  align-items: center;
`;

/*
 ** 스크롤 스타일과 동작을 지정합니다.
 ** 공간에 커서를 가져다 대면, 스타일된 스크롤이 표시됩니다.
 */
const UserContainer = styled.div`
  ::-webkit-scrollbar {
    display: none;
  }
  :hover {
    ::-webkit-scrollbar {
      display: block;
      width: 4px;
      background-color: ${props => props.theme.colors.grey};
    }
    ::-webkit-scrollbar-thumb {
      background-color: ${props => props.theme.colors.main};
      border-radius: 10px;
    }
  }
  // 내눈이 편안하기위한 마진탑 임. 반박시 니말이맞음
  margin-top: 12px;
  overflow-y: scroll;
  height: calc(100% - 52px);
  width: 270px;
`;

const ListBox = styled.div`
  background-color: white;
  border: 2px solid ${props => props.theme.colors.main};
  border-radius: 20px;
  min-width: 300px;
  width: 300px;
  height: calc(100vh - 520px);
  min-height: 340px;
  padding: 17px 23px;
  margin-bottom: 20px;
`;

export default UserList;
