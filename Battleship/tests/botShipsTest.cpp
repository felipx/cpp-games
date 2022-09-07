// botShipsTest.cpp

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
#include "Bot.h"
#include "Ship.h"


int main(void)
{
    Bot bot;
    Ship** ships = bot.getShips();
    Ship* carrier = ships[0];
    Ship* battleship = ships[1];
    Ship* cruiser = ships[2];
    Ship* submarine = ships[3];
    Ship* destroyer = ships[4];

    int i, j, s;
    int step = 0;
    int* p;
    int positions_occupied[17] = {0};

    int* po = bot.getPositions_set();
    std::cout << "positions: ";
    for (i=0; i<17; i++)
    {
        std::cout << po[i] << " ";
    }
    std::cout << std::endl;

    s = carrier->getSize();
    p = carrier->getPosition();
    std::cout << "carrier: ";
    for (i=0; i<s; i++)
    {
        if (p[i] < 1 || p[i] > 100)
        {
            std::cout << "botShipsTest Failed on carrier" << std::endl;
            return -1;
        }
        positions_occupied[i] = p[i];
        std::cout << p[i] << " ";
    }
    step += s;
    std::cout << std::endl;
    std::fill_n (p, s, 0);

    s = battleship->getSize();
    p = battleship->getPosition();
    std::cout << "battleship: ";
    for (i=0; i<17; i++)
    {
        for (j=0; j<s; j++)
        {
            if (p[j] == positions_occupied[i] || p[j] < 1 || p[j] > 100)
            {
                std::cout << "botShipsTest Failed on battleship on " << p[j] << std::endl;
                return -1;
            } 
        }
        if (i<s)
            std::cout << p[i] << " ";
    }
    std::cout << std::endl;
    for (i=step, j=0; j<s; i++, j++)
    {
        positions_occupied[i] = p[j];
    }
    std::fill_n (p, s, 0);
    step += s;
    

    s = cruiser->getSize();
    p = cruiser->getPosition();
    std::cout << "cruiser: ";
    for (i=0; i<17; i++)
    {
        for (j=0; j<s; j++)
        {
            if (p[j] == positions_occupied[i] || p[j] < 1 || p[j] > 100)
            {
                std::cout << "botShipsTest Failed on cruiser on " << p[j] << std::endl;
                return -1;
            }
        }
        if (i<s)
            std::cout << p[i] << " ";
    }
    std::cout << std::endl;
    for (i=step, j=0; j<s; i++, j++)
    {
        positions_occupied[i] = p[j];
    }
    std::fill_n (p, s, 0);
    step += s;

    s = submarine->getSize();
    p = submarine->getPosition();
    std::cout << "submarine: ";
    for (i=0; i<17; i++)
    {
        for (j=0; j<s; j++)
        {
            if (p[j] == positions_occupied[i] || p[j] < 1 || p[j] > 100)
            {
                std::cout << "botShipsTest Failed on submarine on " << p[j] << std::endl;
                return -1;
            }
        }
        if (i<s)
            std::cout << p[i] << " ";
    }
    std::cout << std::endl;
    for (i=step, j=0; j<s; i++, j++)
    {
        positions_occupied[i] = p[j];
    }
    std::fill_n (p, s, 0);
    step += s;

    s = destroyer->getSize();
    p = destroyer->getPosition();
    std::cout << "destroyer: ";
    for (i=0; i<17; i++)
    {
        for (j=0; j<s; j++)
        {
            if (p[j] == positions_occupied[i] || p[j] < 1 || p[j] > 100)
            {
                std::cout << "botShipsTest Failed on destroyer on " << p[j] << std::endl;
                return -1;
            }
        }
        if (i<s)
            std::cout << p[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "botShipsTest Passed" << std::endl;
    
}