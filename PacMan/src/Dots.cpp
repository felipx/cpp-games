// Dots.cpp

#include "Dots.hpp"

Dots::Dots(const int* level, int width, int height)
{
	int i;
	for (i = 0; i < numDots; i++)
	{
		dots[i] = sf::CircleShape(2.f);
		dots[i].setFillColor(sf::Color(255, 255, 0));
		dotsPtr[i] = &dots[i];
	}
	for (i = 0; i < numEnergizers; i++)
	{
		energizers[i] = sf::CircleShape(4.f);
		energizers[i].setFillColor(sf::Color(255, 255, 0));
		energizersPtr[i] = &energizers[i];
	}
	setDots(level, width, height);
}

void Dots::setDots(const int* level, int width, int height)
{
	int i, j, k, e;
	k = 0;
	e = 0;
	// Dot window coordinates
	for (i = 0; i < width; ++i)
		for (j = 0; j < height; ++j)
		{
			// value stored in array
			int tNumber = level[i + j * width];

			if (tNumber == 99)
			{
				// Dot map coordinates
				dots[k].setPosition(sf::Vector2f((float)(i * 16 + 8), (float)(j * 16 + 8)));
				k++;
				if (k > numDots)
					return;
			}
			if (tNumber == 98)
			{
				energizers[e].setPosition(sf::Vector2f((float)(i * 16 + 8), (float)(j * 16 + 8)));
				e++;
				if (e > numDots)
					return;
			}
		}
}

sf::CircleShape** Dots::getDotsPtr()
{
	return dotsPtr;
}

sf::CircleShape** Dots::getEnergizersPtr()
{
	return energizersPtr;
}

int Dots::getNumDots()
{
	return numDots;
}

int Dots::getNumEnergizers()
{
	return numEnergizers;
}

void Dots::nullDotPtr(int i)
{
	dotsPtr[i] = nullptr;
}

void Dots::nullEnergizerPtr(int i)
{
	energizersPtr[i] = nullptr;
}

void Dots::resetPtrs()
{
	int i;
	for (i = 0; i < numDots; i++)
	{
		dotsPtr[i] = &dots[i];
	}
	for (i = 0; i < numEnergizers; i++)
	{
		energizersPtr[i] = &energizers[i];
	}
}