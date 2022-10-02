import React, { useState } from 'react';
import styled from '@emotion/styled';
import Button from '../common/Button';
interface MessageItemProps {
  submitMessage: (message: string) => void;
}

const MessageInput: React.FC<MessageItemProps> = ({ submitMessage }) => {
  const [input, setInput] = useState<string>('');

  const onChangeInput = (e: React.ChangeEvent<HTMLInputElement>) => {
    setInput(e.target.value);
  };

  const handleEnter = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (e.key === 'Enter' && input.length) {
      submitMessage(input);
      setInput('');
    }
  };

  return (
    <ChatInputArea>
      <ChatInputWrap>
        <ChatInput
          type="text"
          onChange={onChangeInput}
          value={input}
          spellCheck={false}
          onKeyPress={handleEnter}
        />
      </ChatInputWrap>
      <Button
        color="main"
        width={100}
        height={50}
        text="전송"
        onClick={() => {
          if (input.length) {
            submitMessage(input);
            setInput('');
          }
        }}
      />
    </ChatInputArea>
  );
};

const ChatInputArea = styled.div`
  display: flex;
  justify-content: center;
  align-items: center;
  margin-top: 10px;
  & button {
    &:disabled {
      background-color: ${({ theme }) => theme.colors.grey};
    }
  }
`;
const ChatInputWrap = styled.div`
  width: 100%;
  height: 50px;
  border: 1px solid ${({ theme }) => theme.colors.main};
  border-radius: 50px;
  margin-right: 10px;
`;
const ChatInput = styled.input`
  display: block;
  width: 100%;
  height: 50px;
  border: none;
  outline: none;
  font-size: 14px;
  background-color: transparent;
  padding: 11px 20px;
`;

export default MessageInput;
