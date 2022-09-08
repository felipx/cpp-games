// Ghost.cpp

#include "Ghost.hpp"

Ghost::Ghost(GhostName name, int tileSize, const std::string& filename, float s, PacMan* p, Map* m)
    : name(name), direction(0), imageCoord(0), updateTime(sf::seconds(0.15f)), map(m), eaten(false),
    pacman(p), strategy(new Chase(this, p, m))
{
    setTileSize(tileSize);
    if (!loadImage(filename + std::to_string(tileSize) + ".png"))
        throw std::runtime_error("Failed to load Image " + filename);
    switch (name)
    {
    case GhostName::Blinky:
        setPosition(180.f, 270.f);
        break;
    case GhostName::Pinky:
        setPosition(200.f, 270.f);
        break;
    case GhostName::Inky:
        setPosition(230.f, 270.f);
        break;
    case GhostName::Clyde:
        setPosition(250.f, 270.f);
        break;
    default:
        break;
    }
    setSpeed(s);
}


void Ghost::setDirection(int d)
{
    direction = d;
}


void Ghost::setEaten()
{
    if (!eaten)
        eaten = true;
    else
        eaten = false;
}


void Ghost::setStrategy(Strategy* s)
{
    delete(strategy);
    strategy = s;
}


int Ghost::getDirection()
{
    return direction;
}


GhostName Ghost::getName()
{
    return name;
}


Strategy* Ghost::getStrategy()
{
    return strategy;
}


bool Ghost::isEaten()
{
    if (eaten)
        return true;
    else
        return false;
}


void Ghost::refreshImage(int mode)
{
    if (mode == 0)
    {
        switch (name)
        {
        case GhostName::Blinky:
            setQuadTextureCoords((float)imageCoord, (float)getTileSize() * 0);
            break;
        case GhostName::Pinky:
            setQuadTextureCoords((float)imageCoord, (float)getTileSize() * 3);
            break;
        case GhostName::Inky:
            setQuadTextureCoords((float)imageCoord, (float)getTileSize() * 1);
            break;
        case GhostName::Clyde:
            setQuadTextureCoords((float)imageCoord, (float)getTileSize() * 2);
            break;
        default:
            break;
        }
    }
    else
    {
        if (!isEaten())
            setQuadTextureCoords((float)imageCoord, (float)getTileSize() * 4);
        else
            setQuadTextureCoords((float)imageCoord, (float)getTileSize() * 5);
    }
        
}


void Ghost::update(int mode,sf::Time deltaTime)
{
    refreshImage(mode);
    updateImageCoord();
}


void Ghost::updateImageCoord()
{
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= updateTime.asSeconds())
    {
        imageCoord += getTileSize();
        if (imageCoord > (getTileSize() * 3))
            imageCoord = 0;
        clock.restart();
    }
}


