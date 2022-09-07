// Positions.cpp

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


#include <chrono>
#include <random>
#include "Positions.h"


Positions::Positions()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1,100);
    int random;

    bool position_set[100];
    for (int i=0; i<100; i++)
    {
        position_set[i] = false;
    }

    int positions_left = 100;
    while (positions_left > 0)
    {
        random = distribution(generator);
        if (!position_set[random-1])
        {
            std::stack<int>* new_position = new std::stack<int>;
            new_position->push(random);
            positions_queue.push(new_position);
            position_set[random-1] = true;
            positions_left--;
        }
    }
}


Positions::~Positions()
{
    while (!positions_queue.empty())
    {
        delete positions_queue.front();
        positions_queue.pop();
    }
}


/*
* Stack new positions after a ship has been hit. 
*/
void Positions::stack_positions(std::stack<int>* s)
{
    int position = s->top();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,3);
    int random, positions_left, i, j;
    int new_position[4] = {position+1, position-1, position+10, position-10};
    bool position_set[4] = {false, false, false, false};
    
    // Hit position is on first row
    if (position < 10 &&  position>1)
    {
        positions_left = 3;
        i = 3;
        j = 100;
    }
    // Hit position is on last row
    else if (position>91 && position<100)
    {
        positions_left = 3;
        i = 2;
        j = 100;
    }
    // Hit position is on first column
    else if ((position % 10) == 1 && position!=1 && position!=91)
    {
        positions_left = 3;
        i = 1;
        j = 100;
    }
    // Hit position is on last column
    else if((position  % 10) == 0  && position !=10 && position !=100)
    {
        positions_left = 3;
        i = 0;
        j = 100;
    }
    // Hit position is on upper left corner
    else if (position == 1)
    {
        positions_left = 2;
        i = 1;
        j = 3;
    }
    // Hit position is on upper right corner
    else if (position == 10)
    {
        positions_left = 2;
        i = 0;
        j = 3;
    }
    // Hit position is on bottom left corner
    else if (position == 91)
    {
        positions_left = 2;
        i = 1;
        j = 2;
    }
    // Hit position is on bottom right corner
    else if (position == 100)
    {
        positions_left = 2;
        i = 0;
        j = 2;
    }
    // Hit position is not in any border
    else
    {
        positions_left = 4;
        i = 100;
        j = 100;
    }

    while(positions_left > 0)
    {
        random = distribution(generator);
        if (random != i && random != j)
        {
            if(!position_set[random])
            {
                s->push(new_position[random]);
                position_set[random] = true;
                positions_left--;
            }
        }
    }
}

std::queue<std::stack<int>*>* Positions::get_positions_queue()
{
    return &positions_queue;
}