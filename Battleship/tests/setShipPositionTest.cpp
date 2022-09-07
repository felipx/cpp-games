// setShipPositionTest.cpp

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
#include "Ship.h"


int main(void)
{
    Ship carrier(ShipClass::Carrier);
    
    int i, s;
    int* p;

    if (carrier.setPosition(0,1))
    {
        std::cout << "setShipPositionTest Failed - carrier(0,1)" << std::endl;
        return -1;
    }
    if (carrier.setPosition(150,1))
    {
        std::cout << "setShipPositionTest Failed - carrier(150,1)" << std::endl;
        return -1;
    }    
    if (carrier.setPosition(50,10))
    {
        std::cout << "setShipPositionTest Failed - carrier(50,10)" << std::endl;
        return -1;
    }
    if (carrier.setPosition(50,0))
    {
        std::cout << "setShipPositionTest Failed - carrier(50,0)" << std::endl;
        return -1;
    }
    if (carrier.setPosition(87,0))
    {
        std::cout << "setShipPositionTest Failed - carrier(87,0)" << std::endl;
        return -1;
    }
    if (carrier.setPosition(87,1))
    {
        std::cout << "setShipPositionTest Failed - carrier(87,0)" << std::endl;
        return -1;
    }
    if (!carrier.setPosition(66,0))
    {
        std::cout << "setShipPositionTest Failed - carrier(66,0)" << std::endl;
        return -1;
    }
    
    p = carrier.getPosition();
    s = carrier.getSize();
    std::cout << "carrier(66,0) position: ";
    for (i=0; i<s; i++)
    {
        if (p[i] != 66+i)
        {
            std::cout << "setShipPositionTest Failed - carrier(66,0) for check" << std::endl;
            return -1;
        }
        std::cout << p[i] << " ";
    }
    std::cout << std::endl;

    if (!carrier.setPosition(45,1))
    {
        std::cout << "setShipPositionTest Failed - carrier(45,1)" << std::endl;
        return -1;
    }
    
    p = carrier.getPosition();
    std::cout << "carrier(45,1) position: ";
    for (i=0; i<s; i++)
    {
        if (p[i] != 45+(10*i))
        {
            std::cout << "setShipPositionTest Failed - carrier(45,1) for check" << std::endl;
            return -1;
        }
        std::cout << p[i] << " ";
    }
    std::cout << std::endl;

    Ship* battleship = new Ship(ShipClass::Battleship);
    Ship* cruiser = new Ship(ShipClass::Cruiser);
    Ship* submarine = new Ship(ShipClass::Submarine);
    Ship* destroyer = new Ship(ShipClass::Destroyer);

    delete battleship;
    delete cruiser;
    delete submarine;
    delete destroyer;

    std::cout << "setShipPositionTest Passed" << std::endl;
}