// Chase.cpp

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