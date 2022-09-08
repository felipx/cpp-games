// Entity.hpp

#ifndef INCLUDE_ENTITY_
#define INCLUDE_ENTITY_

#include "SFML/Graphics.hpp"

constexpr auto DOWN = 0;
constexpr auto LEFT = 1;
constexpr auto RIGHT = 2;
constexpr auto UP = 3;

class Entity : public sf::Drawable, public sf::Transformable
{
public:
    Entity();
    void setPosition(float x, float y);
    void setQuadTextureCoords(float, float);
    void setSpeed(float);
    void setTileSize(int);
    void setVelocity(sf::Vector2f);
    void setVelocity(float, float);
    bool detectCollision(float x, float y);
    sf::Image getImage();
    sf::VertexArray getPosition();
    float getSpeed();
    sf::Texture getTexture();
    int getTileSize();
    sf::Vector2f getVelocity();
    void move(sf::Vector2f);
    void move(float, float);
    bool loadImage(const std::string&);
    void draw(sf::RenderTarget&, sf::RenderStates) const;
    void printPosition(); //debug
private:
    int tileSize;
    float speed;
    sf::Image mImage;
    sf::Texture mTexture;
    sf::Vector2f mVelocity;
    sf::VertexArray quad;

};

#endif /* INCLUDE_ENTITY_ */