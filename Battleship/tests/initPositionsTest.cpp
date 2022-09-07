// initPositionsTest.cpp

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
    std::queue<std::stack<int>*>* positions_queue = positions.get_positions_queue();
    int p[100];

    int i = 0;
    while (!positions_queue->empty())
    {
        p[i] = positions_queue->front()->top();
        delete positions_queue->front();
        positions_queue->pop();
        i++;
    }
    
    int j;
    for (i = 0; i < 100 - 1; i++)
    {
        for (j = 0; j < 100 - i - 1; j++)
        {
            if (p[j] > p[j + 1])
            {
                int temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    
    std::cout << "\n";
    for (i=0 ; i<100; i++)
    {
        if (p[i] != (i+1))
        {
            std::cout << "initPositionsTest Failed" << std::endl;
            return -1;
        }
        std::cout << p[i] << " ";
    }
    std::cout << "\n";

    std::cout << "initPositionsTest Passed" << std::endl;
}
