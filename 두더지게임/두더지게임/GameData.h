#pragma once
class GameData
{
private:
	int gameScore, gameTime, gameStage;
public:

	void InitGameData(int stage);
	void setGameStage(int stage);
	int getGameStage();
	void setGameScore(int data);
	void AddGameScore(int data);
	int getGameScore();
	void setGameTime(int data);
	void SubGameTime(int data);
	int getGameTime();


};