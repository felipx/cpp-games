// Scatter.cpp

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
#include "Scatter.hpp"

Scatter::Scatter(Ghost* g, Map* m)
	: blinkyDirection(0), pinkyDirection(0), inkyDirection(0), clydeDirection(0)
{
	setGhost(g);
	map = m;
	blinkyClock.restart();
}


void Scatter::act(sf::Time deltaTime)
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


void Scatter::actBlinky(sf::Time deltaTime)
{
	if (blinkyDirection == 0)
	{
		blinkyDirection = 1;
		sf::VertexArray blinkyPosition = getGhost()->getPosition();
		float dx = 418.f - blinkyPosition[0].position.x;
		float dy = 65.f - blinkyPosition[0].position.y;

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10);
		int random = dist10(rng);

		if (random > 5)
		{
			if (dx < 0)
			{
				getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
			}
			else
				getGhost()->setVelocity(getGhost()->getSpeed(), 0);
		}
		else
		{
			if (dy < 0)
			{
				getGhost()->setVelocity(0, -getGhost()->getSpeed());
			}
			else
				getGhost()->setVelocity(0, getGhost()->getSpeed());
		}
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	sf::Time elapsed = blinkyClock.getElapsedTime();
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		blinkyDirection = 0;
	}
	if (elapsed.asMilliseconds() > 400)
	{
		blinkyDirection = 0;
		return;
	}
}


void Scatter::actPinky(sf::Time deltaTime)
{
	if (pinkyDirection == 0)
	{
		pinkyDirection = 1;
		sf::VertexArray blinkyPosition = getGhost()->getPosition();
		float dx = 18.f - blinkyPosition[0].position.x;
		float dy = 65.f - blinkyPosition[0].position.y;

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10);
		int random = dist10(rng);

		if (random > 5)
		{
			if (dx < 0)
			{
				getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
			}
			else
				getGhost()->setVelocity(getGhost()->getSpeed(), 0);
		}
		else
		{
			if (dy < 0)
			{
				getGhost()->setVelocity(0, -getGhost()->getSpeed());
			}
			else
				getGhost()->setVelocity(0, getGhost()->getSpeed());
		}
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	sf::Time elapsed = pinkyClock.getElapsedTime();
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		pinkyDirection = 0;
	}
	if (elapsed.asMilliseconds() > 400)
	{
		pinkyDirection = 0;
		return;
	}
}


void Scatter::actInky(sf::Time deltaTime)
{
	if (inkyDirection == 0)
	{
		inkyDirection = 1;
		sf::VertexArray blinkyPosition = getGhost()->getPosition();
		float dx = 418.f - blinkyPosition[0].position.x;
		float dy = 528.f - blinkyPosition[0].position.y;

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10);
		int random = dist10(rng);

		if (random > 5)
		{
			if (dx < 0)
			{
				getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
			}
			else
				getGhost()->setVelocity(getGhost()->getSpeed(), 0);
		}
		else
		{
			if (dy < 0)
			{
				getGhost()->setVelocity(0, -getGhost()->getSpeed());
			}
			else
				getGhost()->setVelocity(0, getGhost()->getSpeed());
		}
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	sf::Time elapsed = inkyClock.getElapsedTime();
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		inkyDirection = 0;
	}
	if (elapsed.asMilliseconds() > 400)
	{
		inkyDirection = 0;
		return;
	}
}


void Scatter::actClyde(sf::Time deltaTime)
{
	if (clydeDirection == 0)
	{
		clydeDirection = 1;
		sf::VertexArray blinkyPosition = getGhost()->getPosition();
		float dx = 18.f - blinkyPosition[0].position.x;
		float dy = 528.f - blinkyPosition[0].position.y;

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist10(0, 10);
		int random = dist10(rng);

		if (random > 5)
		{
			if (dx < 0)
			{
				getGhost()->setVelocity(-getGhost()->getSpeed(), 0);
			}
			else
				getGhost()->setVelocity(getGhost()->getSpeed(), 0);
		}
		else
		{
			if (dy < 0)
			{
				getGhost()->setVelocity(0, -getGhost()->getSpeed());
			}
			else
				getGhost()->setVelocity(0, getGhost()->getSpeed());
		}
	}
	sf::Vector2f d = getGhost()->getVelocity();
	getGhost()->move(getGhost()->getVelocity() * deltaTime.asSeconds());
	// Detect wall collisions
	sf::Time elapsed = clydeClock.getElapsedTime();
	if (map->detectCollision(getGhost()->getPosition()[0].position.x, getGhost()->getPosition()[0].position.y))
	{
		getGhost()->move(-getGhost()->getVelocity() * deltaTime.asSeconds());
		clydeDirection = 0;
	}
	if (elapsed.asMilliseconds() > 400)
	{
		clydeDirection = 0;
		return;
	}
}