#include"GameData.h"


	void GameData::InitGameData(int stage)
	{
		gameScore = 0;
		gameTime = 40;
		gameStage = stage;
	}

	void GameData::setGameStage(int stage)
	{
		gameStage = stage;
	}

	int GameData::getGameStage()
	{
		return gameStage;
	}

	void GameData::setGameScore(int data)
	{
		gameScore = data;
	}

	void GameData::AddGameScore(int data)
	{
		gameScore += data;
	}

	int GameData::getGameScore()
	{
		return gameScore;
	}

	void GameData::setGameTime(int data)
	{
		gameTime = data;
	}

	void GameData::SubGameTime(int data)
	{
		gameTime -= data;
	}

	int GameData::getGameTime()
	{
		return gameTime;
	}
