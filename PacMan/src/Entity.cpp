// Entity.cpp

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

#include <iostream>
#include "Entity.hpp"

Entity::Entity()
	:quad(sf::Quads, 4), speed(0), mImage(), mTexture(), tileSize(16)
{
}


void Entity::setPosition(float x, float y)
{
	quad[0].position = sf::Vector2f(x, y);
	quad[1].position = sf::Vector2f((float)(x + tileSize), y);
	quad[2].position = sf::Vector2f((float)(x + tileSize), (float)(y + tileSize));
	quad[3].position = sf::Vector2f(x, (float)(y + tileSize));
}


void Entity::setQuadTextureCoords(float dx, float dy)
{
	quad[0].texCoords = sf::Vector2f(dx, dy);
	quad[1].texCoords = sf::Vector2f(dx+(float)tileSize, dy);
	quad[2].texCoords = sf::Vector2f(dx+(float)tileSize, dy+(float)tileSize);
	quad[3].texCoords = sf::Vector2f(dx, dy+(float)tileSize);
}


void Entity::setTileSize(int size)
{
	tileSize = size;
}


void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}


void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}


void Entity::setSpeed(float s)
{
	speed = s;
}


sf::Image Entity::getImage()
{
	return mImage;
}


sf::VertexArray Entity::getPosition()
{
	return quad;
}


float Entity::getSpeed()
{
	return speed;
}


sf::Texture Entity::getTexture()
{
	return mTexture;
}


int Entity::getTileSize()
{
	return tileSize;
}


sf::Vector2f Entity::getVelocity()
{
	return mVelocity;
}


bool Entity::detectCollision(float x, float y)
{
	if (getPosition()[0].position.x < x + 13 &&
		getPosition()[0].position.x + 13 > x &&
		getPosition()[0].position.y < y + 13 &&
		getPosition()[0].position.y + 13 > y)
		return true;
	else
		return false;
}


bool Entity::loadImage(const std::string& filename)
{
	if (!mTexture.loadFromFile(filename))
		throw std::runtime_error("Texture failed to load Image");
		return true;
}


void Entity::move(sf::Vector2f d)
{
	quad[0].position.x += d.x;
	quad[0].position.y += d.y;
	quad[1].position.x += d.x;
	quad[1].position.y += d.y;
	quad[2].position.x += d.x;
	quad[2].position.y += d.y;
	quad[3].position.x += d.x;
	quad[3].position.y += d.y;
}


void Entity::move(float x, float y)
{
	quad[0].position.x += x;
	quad[0].position.y += y;
	quad[1].position.x += x;
	quad[1].position.y += y;
	quad[2].position.x += x;
	quad[2].position.y += y;
	quad[3].position.x += x;
	quad[3].position.y += y;
}


void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &mTexture;
	target.draw(quad, states);
}


void Entity::printPosition()
{
	std::cout << "0.x = " << quad[0].position.x << std::endl;
	std::cout << "0.y = " << quad[0].position.y << std::endl;
	std::cout << "1.x = " << quad[1].position.x << std::endl;
	std::cout << "1.y = " << quad[1].position.y << std::endl;
	std::cout << "2.x = " << quad[2].position.x << std::endl;
	std::cout << "2.y = " << quad[2].position.y << std::endl;
	std::cout << "3.x = " << quad[3].position.x << std::endl;
	std::cout << "3.y = " << quad[3].position.y << std::endl;
}
