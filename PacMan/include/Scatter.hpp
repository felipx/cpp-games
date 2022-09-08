// Scatter.hpp

#ifndef INCLUDE_SCATTER_
#define INCLUDE_SCATTER_

#include "SFML/Graphics.hpp"
#include "Ghost.hpp"
#include "Map.hpp"
#include "PacMan.hpp"
#include "Strategy.hpp"

class Scatter : public Strategy
{
public:
	Scatter(Ghost*, Map*);
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
	sf::Clock blinkyClock;
	sf::Clock pinkyClock;
	sf::Clock inkyClock;
	sf::Clock clydeClock;
};

#endif /* INCLUDE_SCATTER_ */
