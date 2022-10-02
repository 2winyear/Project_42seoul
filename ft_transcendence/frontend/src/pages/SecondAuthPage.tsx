import React, { useState, useContext, useEffect } from 'react';
import styled from '@emotion/styled';
import Button from '../components/common/Button';
import { AllContext } from '../store';
import { LOGIN } from '../utils/interface';
import { authAPI } from '../API';
import { useNavigate } from 'react-router-dom';

const SecondAuthPage: React.FC = () => {
  const [authCode, setAuthcode] = useState<string>('');
  const [errMsg, setErrMsg] = useState<string>('');
  const { setUserStatus } = useContext(AllContext).userStatus;
  const { user, setUser } = useContext(AllContext).userData;
  const { jwt, setJwt } = useContext(AllContext).jwtData;
  const navigate = useNavigate();
  let timer: NodeJS.Timer;

  const sendCode = async () => {
    setErrMsg('...');
    clearTimeout(timer);

    timer = setTimeout(async () => {
      if (user) {
        const userId = user.userId; // TODO: user.id user가 null인 경우가 있다고 함
        await authAPI.sendSecondAuthCode(userId, jwt);
        setErrMsg('설정한 메일로 코드가 전송되었습니다.');
      }
    }, 100);
  };

  useEffect(() => {
    if (user) {
      sendCode();
    } else {
      navigate('/'); // logout
    }
    return () => clearTimeout(timer);
  }, []);

  const onCheck = async () => {
    if (user) {
      const res = await authAPI.checkSecondAuthCode(user.userId, Number(authCode), jwt);
      if (res && res.isOk) {
        setErrMsg('인증에 성공하였습니다.');
        window.localStorage.setItem('jwt', res.jwt);
        setUser(LOGIN, {...user, jwt : res.jwt});
        setJwt('SET_JWT', res.jwt);
        timer = setTimeout(() => {
          setUserStatus(LOGIN);
          clearTimeout(timer);
        }, 1000);
      } else {
        setErrMsg('코드가 일치하지 않습니다.');
      }
    } else setErrMsg('다시 시도해주세요.');
  };

  const onGetQuery = () => {
    sendCode();
  };

  const onUpdateAuthCode = (event: React.ChangeEvent<HTMLInputElement>) => {
    setAuthcode(event.target.value);
    setErrMsg('');
  };

  return (
    <Wrap>
      <LoginBox>
        <MainText>등록된 이메일로 받은 코드를 입력해 주세요</MainText>
        <div>
          <Input
            className="input"
            placeholder="인증코드를 입력하세요"
            type="text"
            onChange={onUpdateAuthCode}
            spellCheck={false}
            required
          />
          <SubText>{errMsg}</SubText>
          <ButtonBox>
            <Button color="white" text="코드 재전송" width={130} height={30} onClick={onGetQuery} />
            <Button color="white" text="확인" width={130} height={30} onClick={onCheck} />
          </ButtonBox>
        </div>
      </LoginBox>
    </Wrap>
  );
};

/*
 * 중앙정렬할 자식태그를 위해서 부모태그의 높이를 전체로 수정합니다.
 * 그후 block인 div의 속성을 flex키워드로 바꿔주고 'justify-content' & 'align-items'로 정렬합니다.
 */
const Wrap = styled.div`
  height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
`;

/*
 * 로그인 2차인증을 위한 창 디자인
 * border, border-radius : 외곽선.
 * width, height : 자식으로부터 범위재지정.
 * text-align : 내부 문자를 중앙정렬해줍니다.(center)
 * display, flex-direction, justify-content : 중앙정렬
 */
const LoginBox = styled.div`
  border: 2px solid ${props => props.theme.colors.main};
  border-radius: 20px;
  min-width: 587px;
  width: 587px;
  height: 367px;
  text-align: center;
  display: flex;
  flex-direction: column;
  justify-content: center;
`;

/*
 * 메인텍스트 태그 디자인입니다.(등록된 이메일로 받은 코드를 입력해 주세요)
 */
const MainText = styled.p`
  font-size: 24px;
  margin-top: 30px;
  margin-bottom: 60px;
  font-weight: bold;
  color: ${props => props.theme.colors.main};
`;

/*
 * 인풋창 디자인 (인증코드를 입력하는 곳)
 * boder를 지워버리고 border-bottom만 사용해서 언더바로 스타일링했습니다.
 * 피그마의 인스펙트와 같게 width를 줬습니다. height는 임의값입니다.
 */
const Input = styled.input`
  text-align: center;
  font-size: 14px;
  border: none;
  border-bottom: 1px solid #000;
  width: 256px;
  height: 40px;
  outline: none;
`;

/*
 * 그다음은 서브텍스트 스타일링입니다.
 * "코드가 일치하지 않습니다" 라는 문구를 임시적으로 스타일링 해뒀습니다.
 * 안쪽 패딩값을 통해서, 비율을 맞춰줬습니다.
 * (다현님 피드백에 따라 p태그로 바꿨습니다) ---> span수정 !
 * SubText의 패딩값으로 정렬하지말고, 마진값으로 정렬했습니다.
 * padding: 40px 0; -> margin: 10px 0;
 * font-family: 'Noto Sans KR', sans-serif;가 전역에 설정되어있으니까 빼자
 */
const SubText = styled.span`
  display: block;
  margin: 10px 0;
  color: ${props => props.theme.colors.red};
  font-style: normal;
  font-size: 14px;
  height: 14px;
`;

/*
 * 버튼(코드 재전송, 확인)의 부모태그입니다.
 * 버튼정렬과, 공용버튼의 세부적인 디자인을 지정합니다.
 */
const ButtonBox = styled.div`
  & button {
    border-radius: 5px;
    font-size: 18px;
  }
  & :hover {
    background-color: ${props => props.theme.colors.main};
    color: ${props => props.theme.colors.white};
  }

  padding: 0px 140px;
  display: flex;
  justify-content: center;
  align-items: center;
`;

export default SecondAuthPage;
