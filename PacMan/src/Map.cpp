// Map.cpp

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

#include "Map.hpp"

Map::Map() {}


Map::Map(const std::string& filename, sf::Vector2u textureSize, unsigned int width, unsigned int height)
{
	if(!load(filename + std::to_string(textureSize.x) + ".png", textureSize, level, width, height))
		throw std::runtime_error("Map failed to load Image " + filename);
}


bool Map::load(const std::string& filename, sf::Vector2u textureSize, const int* tiles, unsigned int width, unsigned int height)
{
	if (!textureSet.loadFromFile(filename))
		throw std::runtime_error("Map failed to load Image " + filename);

	unsigned int i = 0;
	unsigned int j;
	unsigned int k = 0;
	unsigned int validTiles = 0;

	while(i < width*height)
	{
		if (*(tiles+i) != 0)
			validTiles++;
		i++;
	}

	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize((long long)validTiles * 4);

	int numTextures = textureSet.getSize().x / textureSize.x;

    int ty = 0;


	for (i = 0; i < width; ++i)
		for (j = 0; j < height; ++j)
		{
			int tNumber = tiles[i + j * width];

			int tx = tNumber % numTextures;

			if (tNumber != 0 && tNumber != 99 && tNumber != 98)
			{
				sf::Vertex* quad = &mVertices[(long long)(k * 4)];
				k++;

				quad[0].position = sf::Vector2f((float)(i * textureSize.x), (float)(j * textureSize.y));
				quad[1].position = sf::Vector2f((float)((i + 1) * textureSize.x), (float)(j * textureSize.y));
				quad[2].position = sf::Vector2f((float)((i + 1) * textureSize.x), (float)((j + 1) * textureSize.y));
				quad[3].position = sf::Vector2f((float)(i * textureSize.x), (float)((j + 1) * textureSize.y));

				quad[0].texCoords = sf::Vector2f((float)(tx * textureSize.x), (float)(ty * textureSize.y));
				quad[1].texCoords = sf::Vector2f((float)((tx + 1) * textureSize.x), (float)(ty * textureSize.y));
				quad[2].texCoords = sf::Vector2f((float)((tx + 1) * textureSize.x), (float)((ty + 1) * textureSize.y));
				quad[3].texCoords = sf::Vector2f((float)(tx * textureSize.x), (float)((ty + 1) * textureSize.y));
			}
		}
	return true;
}


bool Map::detectCollision(float px, float py)
{
	long long i;
	long long numWalls = mVertices.getVertexCount() / 4;
	for (i = 0; i < numWalls; i++)
	{
		sf::Vertex* quad = &mVertices[(long long)(i*4)];
		if (px < quad[0].position.x + 11.5 &&
			px + 11.5 > quad[0].position.x &&
			py < quad[0].position.y + 11.5 &&
			11.5 + py > quad[0].position.y)
			return true;
	}
	return false;
}


void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &textureSet;
	target.draw(mVertices, states);
}
