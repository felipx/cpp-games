// Ship.cpp

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
#include <Ship.h>

Ship::Ship(ShipClass t)
{
    switch (t)
    {
    case ShipClass::Carrier:
        type = ShipClass::Carrier;
        size = 5;
        hits_left = size;
        break;
    case ShipClass::Battleship:
        type = ShipClass::Battleship;
        size = 4;
        hits_left = size;
        break;
    case ShipClass::Cruiser:
        type = ShipClass::Cruiser;
        size = 3;
        hits_left = size;
        break;
    case ShipClass::Submarine:
        type = ShipClass::Submarine;
        size = 3;
        hits_left = size;
        break;
    case ShipClass::Destroyer:
        type = ShipClass::Destroyer;
        size = 2;
        hits_left = size;
        break;
    default:
        throw std::runtime_error("Ship Initialization Failed");
    }
    position = new int[size];
}


Ship::~Ship()
{
    delete[] position;
    position = nullptr;
}


bool Ship::setPosition(int p, int orientation)
{
    if (p < 1 || p > 100 || orientation < 0 || orientation > 1) 
    {
        return false;
    }
    
    int i, j;
    switch (type)
    {
    case ShipClass::Carrier:
        i = 7;
        j = 60;
        break;
    case ShipClass::Battleship:
        i = 8;
        j = 70;
        break;
    case ShipClass::Cruiser:
        i = 9;
        j = 80;
        break;
    case ShipClass::Submarine:
        i = 9;
        j = 80;
        break;
    case ShipClass::Destroyer:
        i = 100;
        j = 90;
        break;
    default:
        throw std::runtime_error("Ship Initialization Failed");
    }

    if (orientation == 0)
    {
        if ( (p % 10) >= i || (p % 10) == 0)
            return false;
        for (i=0; i<size; i++ )
        {
            position[i] = p+i;
        }
        return true;
    }
    else
    {
        if (p > j)
            return false;
        for (i=0; i<size; i++)
        {
            position[i] = p +(i*10);
        }
        return true;
    }
    return false;
}


int* Ship::getPosition()
{
    return position;
}

int Ship::getSize()
{
    return size;
}


bool Ship::hit()
{
    hits_left--;
    if (hits_left < 0)
        throw std::runtime_error("Ship Hits Error");
    if (!hits_left)
        return true;
    else
        return false;
}


void Ship::reset()
{
    hits_left = size;
}