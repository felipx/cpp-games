// Dots.cpp

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