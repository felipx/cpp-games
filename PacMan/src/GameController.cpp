// GameController.cpp

/***********************************************************************************
 * This file is part of PacMan game                                                *
 *                                                                                 *
 * Copyright (C) 2022 felipx                                                       *
 * https://github.com/felipx/                                                      *
 *                                                                                 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy    *
 * of this software and associated documentation files (the "Software"), to deal   *
 * in the Software without restriction, including without limitation the rights    *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is           *
 * furnished to do so, subject to the following conditions:                        *
 * The above copyright notice and this permission notice shall be included in all  *
 * copies or substantial portions of the Software.                                 *
 *                                                                                 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
 * SOFTWARE.                                                                       *
 ***********************************************************************************/

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