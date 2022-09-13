// Entity.cpp

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
#include "Entity.h"


Entity::Entity() : ships_left(5), carrier(ShipClass::Carrier), battleship(ShipClass::Battleship), cruiser(ShipClass::Cruiser), submarine(ShipClass::Submarine), 
            destroyer(ShipClass::Destroyer)
{
    std::fill_n (positions_set, 17, 0);
    std::fill_n (attacked_positions, 100, 0);
}


Ship** Entity::getShips()
{
    return ships;
}


int* Entity::getAttacked_positions()
{
    return attacked_positions;
}


int* Entity::getPositions_set()
{
    return positions_set;
}


bool Entity::set_ships()
{
    return false;
}


int Entity::fire()
{
    return 0;
}


bool Entity::respond(int position)
{
    int s;
    int* p;
    for (Ship* ship : ships)
    {
        s = ship->getSize();
        p = ship->getPosition();
        for (int i=0; i<s; i++)
        {
            if (p[i] == position)
                return true;
        }
    }
    return false;
}