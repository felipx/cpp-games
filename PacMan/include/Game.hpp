// Game.hpp

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

#ifndef INCLUDE_GAME_
#define INCLUDE_GAME_

#include "SFML/Graphics.hpp"
#include "Dots.hpp"
#include "Frightened.hpp"
#include "GameController.hpp"
#include "Ghost.hpp"
#include "Map.hpp"
#include "PacMan.hpp"
#include "Publisher.hpp"
#include "Scatter.hpp"
#include "State.hpp"

class Game : public State
{
public:
	Game(Game& other) = delete;
	void operator=(const Game&) = delete;
	static Game* createGame(GameController*, Publisher*,sf::RenderWindow*, int, int, int);
private:
	Game(GameController*, Publisher*, sf::RenderWindow*, int, int, int);
	void setDifficulty(int);
	void loadHighScore();
	void processScores();
	void render() override;
	void resetGame();
	void update(sf::Time) override;
private:
	static Game* game_;
	PacMan pacman;
	Ghost blinky;
	Ghost pinky;
	Ghost inky;
	Ghost clyde;
	Map map;
	Dots dots;
	int actScore;
	int hScore;
	int dotsLeft;
	int energizersLeft;
	int scatterLeft;
	int lifes;
	bool gameWon;
	bool restart;
	bool onFrighten;
	bool onScatter;
	sf::Clock clock;
	sf::Clock frightenClock;
	sf::Clock scatterClock;
	sf::Text highScore;
	sf::Text winText;
	sf::Text actualScore;
	sf::Texture lifeImage;
	sf::Sprite lifeSprite;
};

#endif /* INCLUDE_GAME_ */