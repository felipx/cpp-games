// Ghost.hpp

#ifndef INCLUDE_GHOST_
#define INCLUDE_GHOST_

#include "SFML/Graphics.hpp"
#include "Chase.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "PacMan.hpp"
#include "Strategy.hpp"

enum class GhostName { Blinky, Pinky, Inky, Clyde };

class Ghost : public Entity
{
public:
    Ghost(GhostName, int, const std::string&, float, PacMan*, Map*);;
    void update(int, sf::Time);
    void updateImageCoord();
    void refreshImage(int);
    bool isEaten();
    void setDirection(int);
    void setEaten();
    void setStrategy(Strategy*);
    int getDirection();
    GhostName getName();
    Strategy* getStrategy();
private:
    GhostName name;
    sf::Clock clock;
    sf::Time updateTime;
    int direction;
    int imageCoord;
    bool eaten;
    Map* map;
    PacMan* pacman;
    Strategy* strategy;
};

#endif /* INCLUDE_GHOSTS_ */