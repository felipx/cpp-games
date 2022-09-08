// PacMan.hpp

#ifndef INCLUDE_PACMAN_
#define INCLUDE_PACMAN_

#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class PacMan : public Entity
{
public:
    PacMan(int, const std::string&, float, Map*);;
    void movePacman(sf::Time);
    void updateImageCoord();
    void updateSprite(int);
    void refreshImage();
    void setDirection(int);
    void setSpritePosition(float, float);
    int getDirection();
    sf::Sprite getSprite();
private:
    sf::Clock clock;
    sf::Time updateTime;
    sf::Texture deadImage;
    sf::Sprite deadSprite;
    int direction;
    int imageCoord;
    Map* map;
};

#endif /* INCLUDE_PACMAN_ */