// GameController.cpp

#include "GameController.hpp"

GameController* GameController::gameController_{ nullptr };

GameController::GameController(int entityTileSize, int mapTileSize)
	: entityTileSize(entityTileSize), mapTileSize(mapTileSize),
	  mWindow(sf::VideoMode(28 * mapTileSize, 36 * mapTileSize), "PacMan"),
	  timePerFrame(sf::seconds(1.f / 60.f)), state(nullptr), difficulty(1)
{
	publisher = Publisher::createPublisher();
}


GameController* GameController::createGameController(int entityTileSize, int mapTileSize)
{
	if (gameController_ == nullptr)
		gameController_ = new GameController(entityTileSize, mapTileSize);
	return gameController_;
}


void GameController::setDifficulty(int d)
{
	difficulty = d;
}


void GameController::setPlayer(std::string p)
{
	player = p;
}


int GameController::getDifficulty()
{
	return difficulty;
}


void GameController::setState(State* s)
{
	state = s;
}


std::string GameController::getPlayer()
{
	return player;
}


void GameController::init()
{
	setTimePerFrame(5.f);
	state = Menu::createMenu(this, publisher ,&mWindow);
}


void GameController::standBy()
{
	if (typeid(Menu).hash_code() == typeid(*state).hash_code())
	{
		setTimePerFrame(1.f);
		state = Game::createGame(this, publisher, &mWindow, entityTileSize, mapTileSize, difficulty);
	}
	else if (typeid(Game).hash_code() == typeid(*state).hash_code())
	{
		setTimePerFrame(5.f);
		state = Menu::createMenu(this, publisher, &mWindow);
	}
}


void GameController::run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		state->processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			state->processEvents();
			state->update(timePerFrame);
		}
		state->render();
	}
}


void GameController::setTimePerFrame(float t)
{
	timePerFrame = sf::seconds(t / 60.f);
}