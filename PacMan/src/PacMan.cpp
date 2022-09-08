// PacMan.cpp

#include "PacMan.hpp"

PacMan::PacMan(int tileSize, const std::string& filename, float s, Map* m)
 : direction(RIGHT), imageCoord(0), updateTime(sf::seconds(0.07f)), map(m)
{
    setTileSize(tileSize);
    if(!loadImage(filename + std::to_string(tileSize) + ".png"))
        throw std::runtime_error("Failed to load Image " + filename);
    setPosition(50.f, 65.f);
    setSpeed(s);
    if (!deadImage.loadFromFile("../media/images/PacmanDeath16.png"))
        throw std::runtime_error("Failed to load deadImage");
    deadSprite.setTexture(deadImage);
    deadSprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
}


void PacMan::movePacman(sf::Time deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        setDirection(UP);
        setVelocity(0,-getSpeed());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        setDirection(DOWN);
        setVelocity(0,getSpeed());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        setDirection(LEFT);
        setVelocity(-getSpeed(),0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        setDirection(RIGHT);
        setVelocity(getSpeed(),0);
    }
    move(getVelocity() * deltaTime.asSeconds());
    // Detecta colision con paredes
    if (map->detectCollision(getPosition()[0].position.x, getPosition()[0].position.y))
        move(-getVelocity() * deltaTime.asSeconds());
    // Vuelve por el otro lado al cruzar el tunel
    if (getPosition()[1].position.x <= -16)
        setPosition(448.f, getPosition()[0].position.y);
    if (getPosition()[0].position.x > 448)
        setPosition(0.f, getPosition()[0].position.y);
    setVelocity(0.f, 0.f);
}


void PacMan::setDirection(int d)
{
    direction = d;
}


void PacMan::setSpritePosition(float x, float y)
{
    deadSprite.setPosition(x, y);
}


int PacMan::getDirection()
{
    return direction;
}


sf::Sprite PacMan::getSprite()
{
    return deadSprite;
}


void PacMan::refreshImage()
{
    if (direction == DOWN)
        setQuadTextureCoords((float)imageCoord, (float)getTileSize()*3);
    if (direction == LEFT)
        setQuadTextureCoords((float)imageCoord, (float)getTileSize()*2);
    if (direction == RIGHT)
        setQuadTextureCoords((float)imageCoord, (float)getTileSize()*0);
    if (direction == UP)
        setQuadTextureCoords((float)imageCoord, (float)getTileSize()*1);
    updateImageCoord();
}


void PacMan::updateImageCoord()
{
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= updateTime.asSeconds())
    {
        imageCoord += getTileSize();
        if (imageCoord > (getTileSize()*5))
            imageCoord = 0;
        clock.restart();
    }
}


void PacMan::updateSprite(int x)
{
    deadSprite.setTextureRect(sf::IntRect(x, 0, getTileSize(), getTileSize()));
}
    