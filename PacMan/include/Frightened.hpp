// Frightened.hpp

#ifndef INCLUDE_FRIGHTENED_
#define INCLUDE_FRIGHTENED_

#include "SFML/Graphics.hpp"
#include "Ghost.hpp"
#include "Map.hpp"
#include "PacMan.hpp"
#include "Strategy.hpp"

class Frightened : public Strategy
{
public:
	Frightened(Ghost*, Map*);
	void act(sf::Time) override;
	void actBlinky(sf::Time);
	void actPinky(sf::Time);
	void actInky(sf::Time);
	void actClyde(sf::Time);
private:
	Map* map;
	int blinkyDirection;
	int pinkyDirection;
	int inkyDirection;
	int clydeDirection;
};

#endif /* INCLUDE_FRIGHTENED_ */