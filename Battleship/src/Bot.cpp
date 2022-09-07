// Bot.cpp

/***********************************************************************************
 * This file is part of Battleship game                                            *
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
#include <chrono>
#include <random>
#include "Bot.h"


Bot::Bot() : Entity()
{    
    set_ships();
}


void Bot::set_ships()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> position_distribution(1,100);
    std::uniform_int_distribution<int> orientation_distribution(0,1);
    int random_position, random_orientation;
    int i, j, k, s;
    int step = 0;
    int* p;
    bool position_found, position_occupied;
    
    for (i=0; i<5; i++)
    {
        s = getShips()[i]->getSize();
        position_found = false;
        while (!position_found)
        {
            position_occupied = false;
            random_position = position_distribution(generator);
            random_orientation = orientation_distribution(generator);
            for (j=0; j<17; j++)
            {
                if (position_occupied)
                    break;
                for (k=0; k<s; k++)
                {
                    if ( (random_orientation == 0) && (random_position + k == getPositions_set()[j]))
                    {
                        position_occupied = true;
                        break;
                    }
                    if ( (random_orientation == 1) && (random_position + (k*10) == getPositions_set()[j]))
                    {
                        position_occupied = true;
                        break;
                    }
                }
            }
            if (getShips()[i]->setPosition(random_position, random_orientation) && !position_occupied)
                position_found = true;
            else
                continue;
            p = getShips()[i]->getPosition();
            for (j=step, k=0; k<s; j++, k++)
            {
                getPositions_set()[j] = p[k];
            }
            step += s;
        }
    }
}