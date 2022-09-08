// Entity.hpp

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