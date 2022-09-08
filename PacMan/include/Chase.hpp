// Chase.hpp

#ifndef INCLUDE_CHASE_
#define INCLUDE_CHASE_

#include "SFML/Graphics.hpp"
#include "Ghost.hpp"
#include "Map.hpp"
#include "PacMan.hpp"
#include "Strategy.hpp"

class Chase : public Strategy
{
public:
	Chase(Ghost*, PacMan*, Map*);
	void act(sf::Time) override;
	void actBlinky(sf::Time);
	void actPinky(sf::Time);
	void actInky(sf::Time);
	void actClyde(sf::Time);
private:
	Map* map;
	PacMan* pacman;
	int blinkyDirection;
	int pinkyDirection;
	int inkyDirection;
	int clydeDirection;
	sf::Clock blinkyClock;
};

#endif /* INCLUDE_CHASE_ */