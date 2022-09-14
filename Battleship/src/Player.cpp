// Player.cpp

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
#include <limits>
#include <string>
#include "Player.h"


Player::Player() : Entity() {} 


// will have to invoke controller from here
bool Player::set_ships()
{
    int p, p1, p2, orientation;
    std::string a;
    std::getline(std::cin, a);
    if (std::cin.fail() || a.size() < 5 || a.size() > 7)
    {
        std::cin.clear();
        return false;
    }

    // Positions are delimited by " "
    if (a.find(" ") == std::string::npos)
        return false;
    
    p = a.find(" ");
    std::string pos1 = a.substr(0,p);
    std::string pos2 = a.substr(p+1);

    p1 = parse_position(pos1);
    p2 = parse_position(pos2);

    if (p1 == -1 || p2 == -1)
        return false;

    int ships_set = getShips_set();
    if (ships_set < 3 && p2-p1+1 == 5-ships_set)
        orientation = 0;
    else if (ships_set < 3 && p2-p1+10 == 50-ships_set*10)
        orientation = 1;
    else if (ships_set >= 3 && p2-p1+1 == 5-ships_set+1)
        orientation = 0;
    else if(ships_set >= 3 && p2-p1+10 == 50-ships_set*10+10)
        orientation = 1;
    else
        return false;
    
    int i, j;
    int s = getShips()[ships_set]->getSize();
    for (i=0; i<17; i++)
    {
        for (j=0; j<s; j++)
        {
            if (orientation == 0 && p1+j == getPositions_set()[i])
                return false;
            if (orientation == 1 && p1+(j*10) == getPositions_set()[i])
                return false;
        }
    }

    bool ship_set;
    ship_set =  getShips()[ships_set]->setPosition(p1, orientation);
     
    if (!ship_set)
        return false;

    int step = 0;
    for (i=0; i<ships_set; i++)
        step += getShips()[i]->getSize();
    for (i=step, j=0; j<s; i++, j++)
    {
        getPositions_set()[i] = getShips()[ships_set]->getPosition()[j];
    }
    return true;
}


int Player::parse_position(std::string position)
{
    int pos_n1, pos_n2;

    // Positions have to be in a-j or A-J range
    if (!((position.data()[0] > 64 && position.data()[0] < 75) || (position.data()[0] > 96 && position.data()[0] < 107)))
        return -1;
    
    if (position.data()[0] > 64 && position.data()[0] < 75)
        pos_n1 = (int) position.data()[0] - 65;
    else
        pos_n1 = (int) position.data()[0] - 97; 

    try
    {
        pos_n2 = std::stoi(position.substr(1));
    }
    catch (const std::invalid_argument& ia) 
    {
        return -1;
    }

    if (pos_n1 < 0 || pos_n1 > 9 || pos_n2 < 1 || pos_n2 > 10)
        return -1;

    return pos_n1*10 + pos_n2;
}


int Player::fire(int p)
{
    if (getAttacked_positions()[p-1] != 0)
        return 0;
    return 1;
}