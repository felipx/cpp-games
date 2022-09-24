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
    while (!positions.get_positions_queue()->empty())
    {
        positions.pop_position_stack();
    }
    
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

    positions.get_positions_queue()->push(position5);
    positions.stack_positions(5);
    if (positions.get_positions_queue()->front()->size() != 4)
    {
        std::cout << "stackPositionsTest Failed on position5" << std::endl;
        return -1;
    }
    std::cout << "position5 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 4 || positions.get_positions_queue()->front()->top() == 6 || positions.get_positions_queue()->front()->top() == 15 || positions.get_positions_queue()->front()->top() == 5))
        {
            std::cout << "\nstackPositionsTest Failed on position5" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position95);
    positions.stack_positions(95);
    if (positions.get_positions_queue()->front()->size() != 4)
    {
        std::cout << "stackPositionsTest Failed on position95" << std::endl;
        return -1;
    }
    std::cout << "position95 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 94 || positions.get_positions_queue()->front()->top() == 96 || positions.get_positions_queue()->front()->top() == 85 || positions.get_positions_queue()->front()->top() == 95))
        {
            std::cout << "\nstackPositionsTest Failed on position95" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position51);
    positions.stack_positions(51);
    if (positions.get_positions_queue()->front()->size() != 4)
    {
        std::cout << "stackPositionsTest Failed on position51" << std::endl;
        return -1;
    }
    std::cout << "position51 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 41 || positions.get_positions_queue()->front()->top() == 61 || positions.get_positions_queue()->front()->top() == 52 || positions.get_positions_queue()->front()->top() == 51))
        {
            std::cout << "\nstackPositionsTest Failed on position51" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position50);
    positions.stack_positions(50);
    if (positions.get_positions_queue()->front()->size()  != 4)
    {
        std::cout << "stackPositionsTest Failed on position50" << std::endl;
        return -1;
    }
    std::cout << "position50 stack size: " << positions.get_positions_queue()->front()->size()  << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 40 || positions.get_positions_queue()->front()->top() == 60 || positions.get_positions_queue()->front()->top() == 49 || positions.get_positions_queue()->front()->top() == 50))
        {
            std::cout << "\nstackPositionsTest Failed on position50" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position1);
    positions.stack_positions(1);
    if (positions.get_positions_queue()->front()->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position1" << std::endl;
        return -1;
    }
    std::cout << "position1 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 2 || positions.get_positions_queue()->front()->top() == 11 || positions.get_positions_queue()->front()->top() == 1))
        {
            std::cout << "\nstackPositionsTest Failed on position1" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position10);
    positions.stack_positions(10);
    if (positions.get_positions_queue()->front()->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position10" << std::endl;
        return -1;
    }
    std::cout << "position10 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 9 || positions.get_positions_queue()->front()->top() == 20 || positions.get_positions_queue()->front()->top() == 10))
        {
            std::cout << "\nstackPositionsTest Failed on position10" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position91);
    positions.stack_positions(91);
    if (positions.get_positions_queue()->front()->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position91" << std::endl;
        return -1;
    }
    std::cout << "position91 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 81 || positions.get_positions_queue()->front()->top() == 92 || positions.get_positions_queue()->front()->top() == 91))
        {
            std::cout << "\nstackPositionsTest Failed on position91" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position100);
    positions.stack_positions(100);
    if (positions.get_positions_queue()->front()->size() != 3)
    {
        std::cout << "stackPositionsTest Failed on position100" << std::endl;
        return -1;
    }
    std::cout << "position100 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 90 || positions.get_positions_queue()->front()->top() == 99 || positions.get_positions_queue()->front()->top() == 100))
        {
            std::cout << "\nstackPositionsTest Failed on position100" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;

    positions.get_positions_queue()->push(position65);
    positions.stack_positions(65);
    if (positions.get_positions_queue()->front()->size() != 5)
    {
        std::cout << "stackPositionsTest Failed on position65" << std::endl;
        return -1;
    }
    std::cout << "position65 stack size: " << positions.get_positions_queue()->front()->size() << " - values: ";
    while (!positions.get_positions_queue()->empty())
    {
        if (!(positions.get_positions_queue()->front()->top() == 64 || positions.get_positions_queue()->front()->top() == 66 || positions.get_positions_queue()->front()->top() == 55 || positions.get_positions_queue()->front()->top() == 75 || position65->top() == 65))
        {
            std::cout << "\nstackPositionsTest Failed on position65" << std::endl;
            return -1;
        }
        std::cout << positions.get_positions_queue()->front()->top() << " ";
        positions.pop_position();
    }
    std::cout << std::endl;


    std::cout << "stackPositionsTest Passed" << std::endl;
}
