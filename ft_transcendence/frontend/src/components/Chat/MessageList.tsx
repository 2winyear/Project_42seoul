import React, { useRef, useEffect } from 'react';
import styled from '@emotion/styled';
import { IMessage } from '../../utils/interface';
import MessageItem from './MessageItem';

interface MessageListProps {
  messages: IMessage[] | [];
}

const MessageList: React.FC<MessageListProps> = ({ messages }) => {
  const messageBoxRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const handleScroll = (e: Event) => {
      e.stopPropagation();
      e.preventDefault();
      const target = e.currentTarget as HTMLDivElement;

      target.scroll({
        top: target.scrollHeight,
        behavior: 'smooth',
      });
    };
    if (messageBoxRef.current) {
      messageBoxRef.current.addEventListener('DOMNodeInserted', handleScroll);
    }

    return () => {
      if (messageBoxRef.current) {
        messageBoxRef.current.removeEventListener('DOMNodeInserted', handleScroll);
      }
    };
  }, []);

  return (
    <MessageListContainer ref={messageBoxRef}>
      <MessageWrapper>
        {messages.length !== 0 &&
          messages.map((message, index) => {
            return <MessageItem key={index} message={message} />;
          })}
      </MessageWrapper>
    </MessageListContainer>
  );
};

const MessageListContainer = styled.div`
  height: calc(100% - 100px);
  border: 1px solid ${({ theme }) => theme.colors.grey};
  overflow-y: scroll !important;
  ::-webkit-scrollbar {
    width: 8px;
    background-color: transparent;
  }
  ::-webkit-scrollbar-thumb {
    background-color: ${({ theme }) => theme.colors.grey};
    :hover {
      background-color: ${({ theme }) => theme.colors.deepGrey};
    }
  }
`;

const MessageWrapper = styled.div`
  padding: 10px;
`;

export default MessageList;
