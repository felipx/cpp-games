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

//debug
#include <chrono>
#include <thread>
//debug


Player::Player() : Entity(), ships_set(0) {} 


int Player::getShips_set()
{
    return ships_set;
}

// will have to invoke controller from here
bool Player::set_ships()
{
    std::string a;
    std::getline(std::cin, a);
    if ( std::cin.fail() || a.size() < 5 || a.size() > 7) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    // if size == 5 postion 10 not used
    if (a.size() == 5)
    {
        std::string pos1 = a.substr(0,2);
        std::cout << pos1 << std::endl;
        if ((*pos1.data() > 64 && *pos1.data() < 75) || (*pos1.data() > 96 && *pos1.data() < 107))
            std::cout << "char:" << *pos1.data() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return false;
}


void Player::setShips_set()
{
    ships_set++;
}