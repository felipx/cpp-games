// Map.cpp

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
