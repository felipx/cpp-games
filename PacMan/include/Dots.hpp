// Dots.hpp

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

#ifndef INCLUDE_DOTS_
#define INCLUDE_DOTS_

#include "SFML/Graphics.hpp"
#include "Map.hpp"

class Dots
{
public:
    Dots(const int*, int, int);
    void setDots(const int*, int, int);
    sf::CircleShape** getDotsPtr();
    sf::CircleShape** getEnergizersPtr();
    int getNumDots();
    int getNumEnergizers();
    void nullDotPtr(int);
    void nullEnergizerPtr(int);
    void resetPtrs();
private:
    static const int numDots{ 284 };     // 284
    static const int numEnergizers{ 4 }; // 4
    sf::CircleShape dots[numDots];
    sf::CircleShape* dotsPtr[numDots]{nullptr};
    sf::CircleShape energizers[numEnergizers];
    sf::CircleShape* energizersPtr[numEnergizers]{ nullptr };
};

#endif /* INCLUDE_DOTS_ */
