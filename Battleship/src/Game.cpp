// Game.cpp

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
#include "Game.h"

#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() std::cout <<"\033[H\033[2J\033[3J"
#endif


Game* Game::game_{ nullptr };


Game::Game(Controller* controller) : State(controller), bot_ready(false), player_ready(false) {}


Game* Game::getInstance(Controller* controller)
{
    if (game_ == nullptr)
    {
        game_ = new Game(controller);
    }
    return game_;
}


void Game::update()
{
    std::cout << "update from game\n";
    if (!bot_ready)
    {
        bool ready = bot.set_ships();
        if (!ready)
            throw std::runtime_error("Bot Initialization Failed");
        else
            bot_ready = true;
    }
    if (!player_ready)
    {
        bool set = player.set_ships();
        if (set)
            player.setShips_set();
        // else cout here????
        if (player.getShips_set() == 5)
            player_ready = true;
    }
    else
    {
        std::string a;
        std::cin >> a;
        if ( std::cin.fail() ) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (a == "Exit" || a == "exit")
            getController()->setExit(true);
        if (a == "Menu" || a == "menu")
        {
            reset();
            getController()->standBy();
        }
    }
}


void Game::render()
{
    int i, j;
    clrscr();
    j = 1;
    printHeader();
    std::cout << "\n                Enemy Ships                                               Player Ships           \n";
    std::cout << "    1   2   3   4   5   6   7   8   9   10                   1   2   3   4   5   6   7   8   9   10\n";
    std::cout << "   _______________________________________                  _______________________________________\n";
    for (i=1; i<=1000; i++)
    {
        if ((i%100 == 1) || (i%100 == 58))
            std::cout << char(65 + i/100);
        else if ((i%100 == 3) || (i%100 == 43) || (i%100 == 60))
            std::cout << "|";
        else if (i%100 == 0)
            std::cout << "|\n";
        else if ( (i%100 == 5) || (i%100 == 9) || (i%100 == 13) || (i%100 == 17) || (i%100 == 21) || 
                  (i%100 == 25) || (i%100 == 29) || (i%100 == 33) || (i%100 == 37) || (i%100 == 41) )
                {
                    if (player.getAttacked_positions()[i-2-3*j-(i/100)*90] == 0)
                    {
                    	std::cout << "o";
                    }
                    else if (player.getAttacked_positions()[i-2-3*j-(i/100)*90] == 1)
                    {
                    	std::cout << "x";
                    }
                        else if (player.getAttacked_positions()[i-2-3*j-(i/100)*90] == 2)
                    {
                        std::cout << "-";
                    }
                    else
                        std::cout << " ";
                    j++;
                    if (j == 11)
                        j = 1;
                }
        else if ( (i%100 == 62) || (i%100 == 66) || (i%100 == 70) || (i%100 == 74) || (i%100 == 78) || 
                  (i%100 == 82) || (i%100 == 86) || (i%100 == 90) || (i%100 == 94) || (i%100 == 98) )
                  {
					if (bot.getAttacked_positions()[i-59-3*j-(i/100)*90] == 0)
					{
						std::cout << "o";
					}
					else if (bot.getAttacked_positions()[i-59-3*j-(i/100)*90] == 1)
					{
						std::cout << "x";
					}
					else if (bot.getAttacked_positions()[i-59-3*j-(i/100)*90] == 2)
					{
						std::cout << "-";
					}
					else
					    std::cout << " ";
					j++;
					if (j == 11)
					    j = 1;
				  }
        else
            std::cout << " ";
    }
    std::cout << "    ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾                 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
    
    if (!player_ready)
    {
        int ships_set = player.getShips_set();
        switch (ships_set)
        {
        case 0:
            std::cout << "Select start and end position for Carrier Ship (5 positions):" << std::endl;
            break;
        case 1:
            std::cout << "Select start and end position for Battleship Ship (4 positions):" << std::endl;
            break;
        case 2:
            std::cout << "Select start and end position for Cruiser Ship (3 positions):" << std::endl;
            break;
        case 3:
            std::cout << "Select start and end position for Submarine (3 positions):" << std::endl;
            break;
        case 4:
            std::cout << "Select start and end position for Destroyer Ship (2 positions):" << std::endl;
            break;
        default:
            throw std::runtime_error("Player Ships Initialization Error");
            break;
        }
    }
}


void Game::reset() {}