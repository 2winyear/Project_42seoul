import React, { useContext, useState, useEffect } from 'react';
import styled from '@emotion/styled';
import LogoImg from '../../assets/logo-white.png';
import {
  MenuType,
  GAME,
  CHAT,
  HOME,
  CHECK_LOGOUT,
  EDIT_CHAT_ROOM,
  IChatRoomInfo,
} from '../../utils/interface';
import { AllContext } from '../../store';
import { useNavigate, useParams } from 'react-router-dom';
import Button from '../common/Button';
import { chatsAPI, gameAPI } from '../../API';

interface HeaderProps {
  type: 'HOME' | 'CHAT' | 'GAME';
}

const Header: React.FC<HeaderProps> = ({ type }) => {
  const { setModal } = useContext(AllContext).modalData;
  const { user } = useContext(AllContext).userData;
  const navigate = useNavigate();
  const { roomId } = useParams();
  const [, setRoomInfo] = useState<IChatRoomInfo | null>();
  const [isOwner, setIsOwner] = useState<boolean>(false);
  const [clickedMenu, setClickedMenu] = useState<MenuType | 'HOME' | null>();

  const onClickMenu = (menu: MenuType | 'HOME') => {
    if (clickedMenu === menu) return;
    switch (menu) {
      case HOME:
        setClickedMenu(menu);
        navigate('/');
        return;
      case GAME:
        setClickedMenu(menu);
        navigate('/game');
        return;
      case CHAT:
        setClickedMenu(menu);
        navigate('/chat');
        return;
      default:
        return;
    }
  };

  //1925*
  const onClickExitBtn = async (type: string) => {
    if (user && roomId) {
      if (type === CHAT) {
        await chatsAPI.leaveChatRoom(+roomId, user.userId, user.jwt);
        onClickMenu(CHAT);
      } else if (type === GAME) {
        await gameAPI.leaveGameRoom(+roomId, user.userId, user.jwt);
        onClickMenu(GAME);
      }
    }
  };

  const onSetupRoom = () => {
    if (user && roomId) {
      setModal(EDIT_CHAT_ROOM, user.userId, +roomId);
    }
  };

  useEffect(() => {
    const getRoomInfo = async () => {
      if (roomId && user) {
        if (type === CHAT) {
          const res = await chatsAPI.getChatRoomStatus(+roomId, user.jwt);
          setRoomInfo(res);
          if (res && res.ownerId == user.userId) setIsOwner(true);
        } else if (type === GAME) {
          // TODO: const roomInfo = await gameAPI.getGameRoomStatus(+roomId, user.jwt);
          // setRoomInfo(roomInfo);
        }
      }
    };
    getRoomInfo();
  }, [roomId, user]);

  return (
    <HeaderContainer>
      <LogoWrap onClick={() => onClickMenu(HOME)}>
        <Logo src={LogoImg} alt="Home" />
      </LogoWrap>
      {
        {
          HOME: (
            <Menus>
              <Menu onClick={() => onClickMenu(GAME)}>GAME</Menu>
              <Menu onClick={() => onClickMenu(CHAT)}>CHAT</Menu>
              <Menu onClick={() => setModal(CHECK_LOGOUT)}>LOGOUT</Menu>
            </Menus>
          ),
          CHAT: (
            <Menus>
              {isOwner && (
                <Button
                  color="white"
                  text="방 설정"
                  width={140}
                  height={50}
                  onClick={onSetupRoom}
                />
              )}
              <Button
                color="white"
                text="방 나가기"
                width={140}
                height={50}
                onClick={() => onClickExitBtn(CHAT)}
              />
            </Menus>
          ),
          GAME: (
            <Menus>
              <Button
                color="white"
                text="방 나가기"
                width={140}
                height={50}
                onClick={() => onClickExitBtn(GAME)}
              />
            </Menus>
          ),
        }[type]
      }
    </HeaderContainer>
  );
};

const HeaderContainer = styled.header`
  width: 100%;
  height: 100px;
  display: flex;
  justify-content: space-between;
  align-items: end;
  padding: 15px 0;
  margin-bottom: 20px;
`;
const LogoWrap = styled.div`
  width: 300px;
`;
const Logo = styled.img`
  width: 100%;
  height: 100%;
  object-fit: contain;
  user-select: none;

  cursor: pointer;
`;
const Menus = styled.nav`
  display: flex;
  & button {
    margin-left: 18px;
  }
`;
const Menu = styled.span`
  display: inline-block;
  width: 100px;
  color: white;
  font-size: 20px;
  text-align: center;
  cursor: pointer;
  user-select: none;
  &:hover {
    color: ${({ theme }) => theme.colors.lightBlue};
  }
`;

export default Header;
