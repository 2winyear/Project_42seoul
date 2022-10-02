import React, { useContext } from 'react';
import styled from '@emotion/styled';
import { IMessage } from '../../utils/interface';
import ProfileImage from '../common/ProfileImage';
import { AllContext } from '../../store';
interface MessageItemProps {
  message: IMessage;
}

const getTime = (time: string | number): string => {
  const date = new Date(time);
  const hours = date.getHours() < 10 ? `0${date.getHours()}` : date.getHours();
  const minutes = date.getMinutes() < 10 ? `0${date.getMinutes()}` : date.getMinutes();

  return `${hours}:${minutes}`;
};

const MessageItem: React.FC<MessageItemProps> = ({ message }) => {
  const { user } = useContext(AllContext).userData;

  if (message.isBroadcast) return <BroadcastMsg>{message.message}</BroadcastMsg>;
  else {
    return (
      <>
        {message && user && (
          <MessageItemContainer fromUser={message.userId === user.userId}>
            {message.userId !== user.userId && <ProfileImage src={message.avatar} size={40} />}
            <MessageWrapper fromUser={message.userId === user.userId}>
              {message.userId !== user.userId && <MessageName>{message.nickname}</MessageName>}
              <MessageContent>
                {message.userId === user.userId && (
                  <MessageTime>{getTime(message.createdTime)}</MessageTime>
                )}
                <MessageBox>{message.message}</MessageBox>
                {message.userId !== user.userId && (
                  <MessageTime>{getTime(message.createdTime)}</MessageTime>
                )}
              </MessageContent>
            </MessageWrapper>
          </MessageItemContainer>
        )}
      </>
    );
  }
};

const BroadcastMsg = styled.span`
  display: inline-block;
  width: 100%;
  padding: 10px;
  color: ${({ theme }) => theme.colors.deepGrey};
  text-align: center;
  font-size: 12px;
`;

const MessageItemContainer = styled.div<{ fromUser: boolean }>`
  display: flex;
  align-items: flex-start;
  justify-content: ${props => (props.fromUser ? 'flex-end' : 'flex-start')};
  margin-bottom: 10px;
`;

const MessageWrapper = styled.div<{ fromUser: boolean }>`
  text-align: ${props => (props.fromUser ? 'right' : 'left')};
  max-width: 70%;
  margin-left: 10px;
`;
const MessageName = styled.span`
  display: block;
  font-size: 16px;
  font-weight: bold;
  margin-bottom: 10px;
`;
const MessageContent = styled.div`
  display: flex;
  align-items: flex-end;
  width: 100%;
`;

const MessageBox = styled.p`
  display: block;
  background-color: ${({ theme }) => theme.colors.grey};
  border-radius: 10px;
  padding: 10px 10px;
  word-wrap: break-spaces;
  word-break: break-all;
  max-width: 100%;
`;
const MessageTime = styled.span`
  font-size: 12px;
  color: ${({ theme }) => theme.colors.deepGrey};
  margin: 0 8px;
  padding-bottom: 5px;
`;

export default MessageItem;
