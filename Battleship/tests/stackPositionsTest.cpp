// stackPositionsTest.cpp

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
#include "Positions.h"


int main(void)
{
    Positions positions;
    //std::queue<std::stack<int>*>* positions_queue = positions.get_positions_queue();
    
    std::stack<int>* position5 = new std::stack<int>;
    position5->push(5);
    std::stack<int>* position95 = new std::stack<int>;
    position95->push(95);
    std::stack<int>* position51 = new std::stack<int>;
    position51->push(51);
    std::stack<int>* position50 = new std::stack<int>;
    position50->push(50);
    std::stack<int>* position1 = new std::stack<int>;
    position1->push(1);
    std::stack<int>* position10 = new std::stack<int>;
    position10->push(10);
    std::stack<int>* position91 = new std::stack<int>;
    position91->push(91);
    std::stack<int>* position100 = new std::stack<int>;
    position100->push(100);
    std::stack<int>* position65 = new std::stack<int>;
    position65->push(65);

    positions.stack_positions(position5);
    if (position5->size() != 4)
    {
        std::cout << "stackPositionsTest Failed on position5" << std::endl;
        return -1;
    }
    std::cout << "position5 stack size: " << position5->size() << " - values: ";
    while (!position5->empty())
    {
        if (!(position5->top() == 4 || position5->top() == 6 || position5->top() == 15 || position5->top() == 5))
        {
            std::cout << "\nstackPositionsTest Failed on position5" << std::endl;
            return -1;
        }
        std::cout << position5->top() << " ";
        position5->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position95);
    if (position95->size() != 4)
    {
        std::cout << "stackPositionsTest Failed on position95" << std::endl;
        return -1;
    }
    std::cout << "position95 stack size: " << position95->size() << " - values: ";
    while (!position95->empty())
    {
        if (!(position95->top() == 94 || position95->top() == 96 || position95->top() == 85 || position95->top() == 95))
        {
            std::cout << "\nstackPositionsTest Failed on position95" << std::endl;
            return -1;
        }
        std::cout << position95->top() << " ";
        position95->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position51);
    if (position51->size() != 4)
    {
        std::cout << "stackPositionsTest Failed on position51" << std::endl;
        return -1;
    }
    std::cout << "position51 stack size: " << position51->size() << " - values: ";
    while (!position51->empty())
    {
        if (!(position51->top() == 41 || position51->top() == 61 || position51->top() == 52 || position51->top() == 51))
        {
            std::cout << "\nstackPositionsTest Failed on position51" << std::endl;
            return -1;
        }
        std::cout << position51->top() << " ";
        position51->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position50);
    if (position50->size() != 4)
    {
        std::cout << "stackPositionsTest Failed on position50" << std::endl;
        return -1;
    }
    std::cout << "position50 stack size: " << position50->size() << " - values: ";
    while (!position50->empty())
    {
        if (!(position50->top() == 40 || position50->top() == 60 || position50->top() == 49 || position50->top() == 50))
        {
            std::cout << "\nstackPositionsTest Failed on position50" << std::endl;
            return -1;
        }
        std::cout << position50->top() << " ";
        position50->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position1);
    if (position1->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position1" << std::endl;
        return -1;
    }
    std::cout << "position1 stack size: " << position1->size() << " - values: ";
    while (!position1->empty())
    {
        if (!(position1->top() == 2 || position1->top() == 11 || position1->top() == 1))
        {
            std::cout << "\nstackPositionsTest Failed on position1" << std::endl;
            return -1;
        }
        std::cout << position1->top() << " ";
        position1->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position10);
    if (position10->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position10" << std::endl;
        return -1;
    }
    std::cout << "position10 stack size: " << position10->size() << " - values: ";
    while (!position10->empty())
    {
        if (!(position10->top() == 9 || position10->top() == 20 || position10->top() == 10))
        {
            std::cout << "\nstackPositionsTest Failed on position10" << std::endl;
            return -1;
        }
        std::cout << position10->top() << " ";
        position10->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position91);
    if (position91->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position91" << std::endl;
        return -1;
    }
    std::cout << "position91 stack size: " << position91->size() << " - values: ";
    while (!position91->empty())
    {
        if (!(position91->top() == 81 || position91->top() == 92 || position91->top() == 91))
        {
            std::cout << "\nstackPositionsTest Failed on position91" << std::endl;
            return -1;
        }
        std::cout << position91->top() << " ";
        position91->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position100);
    if (position100->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position100" << std::endl;
        return -1;
    }
    std::cout << "position100 stack size: " << position100->size() << " - values: ";
    while (!position100->empty())
    {
        if (!(position100->top() == 90 || position100->top() == 99 || position100->top() == 100))
        {
            std::cout << "\nstackPositionsTest Failed on position100" << std::endl;
            return -1;
        }
        std::cout << position100->top() << " ";
        position100->pop();
    }
    std::cout << std::endl;

    positions.stack_positions(position65);
    if (position65->size() != 5)
    {
        std::cout << "stackPositionsTest Failed on position65" << std::endl;
        return -1;
    }
    std::cout << "position65 stack size: " << position65->size() << " - values: ";
    while (!position65->empty())
    {
        if (!(position65->top() == 64 || position65->top() == 66 || position65->top() == 55 || position65->top() == 75 || position65->top() == 65))
        {
            std::cout << "\nstackPositionsTest Failed on position65" << std::endl;
            return -1;
        }
        std::cout << position65->top() << " ";
        position65->pop();
    }
    std::cout << std::endl;


    std::cout << "stackPositionsTest Passed" << std::endl;
}
