// GameController.hpp

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

#ifndef INCLUDE_GAMECONTROLLER_ 
#define INCLUDE_GAMECONTROLLER_

#include "Game.hpp"
#include "Menu.hpp"
#include "Publisher.hpp"
#include "State.hpp"

class GameController
{
public:
	GameController(GameController& other) = delete;
	void operator=(const GameController&) = delete;
	static GameController* createGameController(int, int);
	void setDifficulty(int);
	void setPlayer(std::string);
	void setState(State*);
	int getDifficulty();
	std::string getPlayer();
	void init();
	void standBy();
	void run();
private:
	GameController(int, int);
	void setTimePerFrame(float t);
private:
	static GameController* gameController_;
	Publisher* publisher;
	State* state;
	sf::RenderWindow mWindow;
	sf::Clock clock;
	sf::Time timePerFrame;
	int entityTileSize;
	int mapTileSize;
	int difficulty;
	std::string player{""};
};

#endif /* INCLUDE_GAMECONTROLLER_ */
