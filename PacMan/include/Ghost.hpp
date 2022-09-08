// Ghost.hpp

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

#ifndef INCLUDE_GHOST_
#define INCLUDE_GHOST_

#include "SFML/Graphics.hpp"
#include "Chase.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "PacMan.hpp"
#include "Strategy.hpp"

enum class GhostName { Blinky, Pinky, Inky, Clyde };

class Ghost : public Entity
{
public:
    Ghost(GhostName, int, const std::string&, float, PacMan*, Map*);;
    void update(int, sf::Time);
    void updateImageCoord();
    void refreshImage(int);
    bool isEaten();
    void setDirection(int);
    void setEaten();
    void setStrategy(Strategy*);
    int getDirection();
    GhostName getName();
    Strategy* getStrategy();
private:
    GhostName name;
    sf::Clock clock;
    sf::Time updateTime;
    int direction;
    int imageCoord;
    bool eaten;
    Map* map;
    PacMan* pacman;
    Strategy* strategy;
};

#endif /* INCLUDE_GHOSTS_ */