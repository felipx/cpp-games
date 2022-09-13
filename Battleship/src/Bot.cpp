// Bot.cpp

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
#include <chrono>
#include <random>
#include "Bot.h"


Bot::Bot() : Entity(), last_attack(0)
{    
    set_ships();
}

Positions* Bot::getAttack_positions()
{
    return &attack_positions;
}


int Bot::getLast_attack()
{
    return last_attack;
}

void Bot::setLast_attack(int p)
{
    last_attack = p;
}


bool Bot::set_ships()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> position_distribution(1,100);
    std::uniform_int_distribution<int> orientation_distribution(0,1);
    int random_position, random_orientation;
    int i, j, k, s;
    int step = 0;
    int* p;
    bool position_found, position_occupied;
    
    for (i=0; i<5; i++)
    {
        s = getShips()[i]->getSize();
        position_found = false;
        while (!position_found)
        {
            position_occupied = false;
            random_position = position_distribution(generator);
            random_orientation = orientation_distribution(generator);
            for (j=0; j<17; j++)
            {
                if (position_occupied)
                    break;
                for (k=0; k<s; k++)
                {
                    if ( (random_orientation == 0) && (random_position + k == getPositions_set()[j]))
                    {
                        position_occupied = true;
                        break;
                    }
                    if ( (random_orientation == 1) && (random_position + (k*10) == getPositions_set()[j]))
                    {
                        position_occupied = true;
                        break;
                    }
                }
            }
            if (getShips()[i]->setPosition(random_position, random_orientation) && !position_occupied)
                position_found = true;
            else
                continue;
            p = getShips()[i]->getPosition();
            for (j=step, k=0; k<s; j++, k++)
            {
                getPositions_set()[j] = p[k];
            }
            step += s;
        }
    }
    for (i=0; i<17; i++)
    {
        if (getPositions_set()[i] == 0)
            return false;
    }
    return true;
}


int Bot::fire()
{
    int p;
    bool fire_ready = false;
    while (!fire_ready)
    {
        for (int i=0; i<100; i++)
        {
            if (getAttacked_positions()[attack_positions.get_positions_queue()->front()->top() -1 ] != 0)
            {
                attack_positions.pop_position();
                break;
            }
        }
        fire_ready = true;
    }
    p = attack_positions.get_positions_queue()->front()->top();
    attack_positions.pop_position();
    return p;
}


bool Bot::stack_position(int p)
{
    for (int i=0; i<100; i++)
    {
        if (p == getAttacked_positions()[i])
            return false;
    }
    attack_positions.get_positions_queue()->front()->push(p);
    return true;
}


void Bot::stack_next(int attack_pos)
{
    int delta;
    if (attack_pos-getLast_attack() > 0 && attack_pos-getLast_attack() < 10)
        delta = 1;
    if (attack_pos-getLast_attack() >= 10)
        delta = 10;
    if (attack_pos-getLast_attack() < 0 && attack_pos-getLast_attack() > -10)
        delta = -1;
    if (attack_pos-getLast_attack() <= -10)
        delta = -10;
    if (//((attack_pos+(attack_pos-getLast_attack())+1) % 10 != 1) && ((attack_pos+(attack_pos-getLast_attack())-1) % 10 != 0) && 
        (attack_pos+delta > 0) && (attack_pos+delta < 101))
    {
        stack_position(attack_pos+delta);
        //stack_position(attack_pos+(attack_pos-getLast_attack()));
    }
}