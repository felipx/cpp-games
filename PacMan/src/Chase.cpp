// Chase.cpp

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

#include <random>
#include "SFML/Graphics.hpp"
#include "Chase.hpp"

Chase::Chase(Ghost* g, PacMan* p, Map* m)
	: blinkyDirection(0), pinkyDirection(0), inkyDirection(0), clydeDirection(0)
{
	setGhost(g);
	pacman = p;
	map = m;
	blinkyClock.restart();
}


void Chase::act(sf::Time deltaTime)
{
	getGhost()->update(0, deltaTime);
	switch (getGhost()->getName())
	{
	case GhostName::Blinky:
		actBlinky(deltaTime);
		break;
	case GhostName::Pinky:
		actPinky(deltaTime);
		break;
	case GhostName::Inky:
		actInky(deltaTime);
		break;
	case GhostName::Clyde:
		actClyde(deltaTime);
		break;
	default:
		break;
	}
}


void Chase::actBlinky(sf::Time deltaTime)
{
	if (clydeDirection == 0)
	{
		clydeDirection = 1;
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
		int random = dist4(rng);

		if (random == 3)
			getGhost()->setVelocity(0, -getGhost()->getSpeed());
		if (random == 0)
			getGhost()->setVelocity(0, getGhost()->getSpeed());
		if (random == 1)
			getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
		if (random == 2)
			getGhost()->setVelocity(getGhost()->getSpeed(), 0);
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		clydeDirection = 0;
	}
}


void Chase::actPinky(sf::Time deltaTime)
{
	if (clydeDirection == 0)
	{
		clydeDirection = 1;
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
		int random = dist4(rng);

		if (random == 3)
			getGhost()->setVelocity(0, -getGhost()->getSpeed());
		if (random == 0)
			getGhost()->setVelocity(0, getGhost()->getSpeed());
		if (random == 1)
			getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
		if (random == 2)
			getGhost()->setVelocity(getGhost()->getSpeed(), 0);
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		clydeDirection = 0;
	}
}


void Chase::actInky(sf::Time deltaTime)
{
	if (clydeDirection == 0)
	{
		clydeDirection = 1;
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
		int random = dist4(rng);

		if (random == 3)
			getGhost()->setVelocity(0, -getGhost()->getSpeed());
		if (random == 0)
			getGhost()->setVelocity(0, getGhost()->getSpeed());
		if (random == 1)
			getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
		if (random == 2)
			getGhost()->setVelocity(getGhost()->getSpeed(), 0);
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		clydeDirection = 0;
	}
}


void Chase::actClyde(sf::Time deltaTime)
{
	if (clydeDirection == 0)
	{
		clydeDirection = 1;
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
		int random = dist4(rng);

		if (random == 3)
			getGhost()->setVelocity(0, -getGhost()->getSpeed());
		if (random == 0)
			getGhost()->setVelocity(0, getGhost()->getSpeed());
		if (random == 1)
			getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
		if (random == 2)
			getGhost()->setVelocity(getGhost()->getSpeed(), 0);
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		clydeDirection = 0;
	}
}