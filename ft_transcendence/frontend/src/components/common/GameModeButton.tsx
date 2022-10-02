import React from 'react';
import { GameMode } from '../../utils/interface';

interface IGameModeButton {
  gameMode: GameMode;
  setGameMode: React.Dispatch<React.SetStateAction<GameMode>>;
}

const GameModeButton: React.FC<IGameModeButton> = ({ gameMode, setGameMode }) => {
  const onRadioClick = (e: React.ChangeEvent<HTMLInputElement>) => {
    setGameMode(e.target.value as GameMode);
  };
  return (
    <>
      <div className="radio">
        <label>
          <input
            type="radio"
            value="normal"
            onChange={onRadioClick}
            checked={'normal' === gameMode}
          />
          normal
        </label>
        <label>
          <input
            type="radio"
            value="speed"
            onChange={onRadioClick}
            checked={'speed' === gameMode}
          />
          speed up
        </label>
        <label>
          <input
            type="radio"
            value="obstacle"
            onChange={onRadioClick}
            checked={'obstacle' === gameMode}
          />
          obstacle
        </label>
      </div>
    </>
  );
};

export default GameModeButton;
