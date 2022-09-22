// Demo.cpp

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
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include "Demo.h"

#ifdef _WIN32
//#define clrscr() std::cout <<"\033[H\033[2J\033[3J"
#define clrscr() system("cls")
#else
#define clrscr() std::cout <<"\033[H\033[2J\033[3J"
#endif


Demo* Demo::demo_{ nullptr };


Demo::Demo(Controller* controller) : State(controller), bot1_ready(false), bot2_ready(false), bot1_attack_pos(0), 
                                     bot2_attack_pos(0), bot1_last_hit(false), bot2_last_hit(false), bot2_turn(false), 
                                     game_over(false) {}


Demo* Demo::getInstance(Controller* controller)
{
    if (demo_ == nullptr)
    {
        demo_ = new Demo(controller);
    }
    return demo_;
}


void Demo::update()
{
    if (!bot1_ready)
    {
        bool ready = bot1.set_ships();
        if (!ready)
            throw std::runtime_error("Bot Initialization Failed");
        else
            bot1_ready = true;
    }
    if (!bot2_ready)
    {
        bool ready = bot2.set_ships();
        if (!ready)
            throw std::runtime_error("Bot Initialization Failed");
        else
            bot2_ready = true;
    }
    
    if (bot1_ready && bot2_ready && !game_over)
    {
        // Bot1 attack starts here
        if (!bot2_turn)
        {
            if (!bot1.getAttack_positions()->isStacked())
            {
                bot1_attack_pos = bot1.fire();
                bot1.setLast_attack(bot1_attack_pos);
                if (bot2.respond(bot1_attack_pos))    
                {
                    bot1.getAttacked_positions()[bot1_attack_pos-1] = 1;
                    bot1_last_hit = true;
                    bot1.getAttack_positions()->stack_positions(bot1_attack_pos);
                    if (bot2.isDefeated())
                    {
                    game_over = true;
                    return;
                    }
                    render(); // render call
                }
                else
                {
                    bot1.getAttacked_positions()[bot1_attack_pos-1] = 2;
                    bot1_last_hit = false;
                    bot2_turn = true;
                    return;
                }
            }
            bool firing = true;
            while (firing)
            {
                bot1_attack_pos = bot1.fire();
                if (bot2.respond(bot1_attack_pos))
                {
                    bot1.getAttacked_positions()[bot1_attack_pos-1] = 1;
                    bot1_last_hit = true;
                    if (bot2.isDefeated())
                    {
                        game_over = true;
                        return;
                    }
                    render(); // render call
                    bot1.stack_next(bot1_attack_pos);
                }
                else
                {
                    bot1.getAttacked_positions()[bot1_attack_pos-1] = 2;
                    bot1_last_hit = false;
                    firing = false;
                    bot2_turn = true;
                }
            }
        }

        // Bot2 attack starts here
        if (bot2_turn)
        {
            if (!bot2.getAttack_positions()->isStacked())
            {
                bot2_attack_pos = bot2.fire();
                bot2.setLast_attack(bot2_attack_pos);
                if (bot1.respond(bot2_attack_pos))    
                {
                    bot2.getAttacked_positions()[bot2_attack_pos-1] = 1;
                    bot2_last_hit = true;
                    bot2.getAttack_positions()->stack_positions(bot2_attack_pos);
                    if (bot1.isDefeated())
                    {
                    game_over = true;
                    return;
                    }
                    render(); // render call
                }
                else
                {
                    bot2.getAttacked_positions()[bot2_attack_pos-1] = 2;
                    bot2_last_hit = false;
                    bot2_turn = false;
                    return;
                }
            }
            bool firing = true;
            while (firing)
            {
                bot2_attack_pos = bot2.fire();
                if (bot1.respond(bot2_attack_pos))
                {
                    bot2.getAttacked_positions()[bot2_attack_pos-1] = 1;
                    bot2_last_hit = true;
                    if (bot1.isDefeated())
                    {
                        game_over = true;
                        return;
                    }
                    render(); // render call
                    bot2.stack_next(bot2_attack_pos);
                }
                else
                {
                    bot2.getAttacked_positions()[bot2_attack_pos-1] = 2;
                    bot2_last_hit = false;
                    firing = false;
                    bot2_turn = false;
                }
            }
        }
        bot2_turn = false;
    }
    if (game_over)
    {
        std::string a;
        std::getline(std::cin, a);
        reset();
        getController()->standBy(0);
    }
}


void Demo::render()
{
    int i, j, k;
    clrscr();
    j = 1;
    printHeader();
    std::cout << "\n                Player 1 Ships                                            Player 2 Ships          \n";
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
                    bool set = false;
                    for (k=0; k<17; k++)
                    {
                        if (bot1.getPositions_set()[k] == i-1-3*j-(i/100)*90 && bot2.getAttacked_positions()[i-2-3*j-(i/100)*90] == 0)
                        {
                            std::cout << "v";
                            set = true;
                            break;
                        }
                        if (bot1.getPositions_set()[k] == i-1-3*j-(i/100)*90 && bot2.getAttacked_positions()[i-2-3*j-(i/100)*90] == 1)
                        {
                            std::cout << "x";
                            set = true;
                            break;
                        }
                    }
                    if (!set)
                    {
                        if (bot2.getAttacked_positions()[i-2-3*j-(i/100)*90] == 2)
                            std::cout << "-";
                        else
                            std::cout << "o";
                    }
					j++;
					if (j == 11)
					    j = 1;
                }
        else if ( (i%100 == 62) || (i%100 == 66) || (i%100 == 70) || (i%100 == 74) || (i%100 == 78) || 
                  (i%100 == 82) || (i%100 == 86) || (i%100 == 90) || (i%100 == 94) || (i%100 == 98) )
                  {
                    bool set = false;
                    for (k=0; k<17; k++)
                    {
                        if (bot2.getPositions_set()[k] == i-58-3*j-(i/100)*90 && bot1.getAttacked_positions()[i-59-3*j-(i/100)*90] == 0)
                        {
                            std::cout << "v";
                            set = true;
                            break;
                        }
                        if (bot2.getPositions_set()[k] == i-58-3*j-(i/100)*90 && bot1.getAttacked_positions()[i-59-3*j-(i/100)*90] == 1)
                        {
                            std::cout << "x";
                            set = true;
                            break;
                        }
                    }
                    if (!set)
                    {
                        if (bot1.getAttacked_positions()[i-59-3*j-(i/100)*90] == 2)
                            std::cout << "-";
                        else
                            std::cout << "o";
                    }
					j++;
					if (j == 11)
					    j = 1;
				  }
        else
            std::cout << " ";
    }
    #ifdef _WIN32
    std::cout << "   ---------------------------------------                  ---------------------------------------\n";
    #else
    std::cout << "   ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾                  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
    #endif
    
    
    if (bot1_ready && bot2_ready && !game_over)
    {
        std::string bot1_pos;
        std::string bot2_pos;
        if (bot1_attack_pos == 0)
            bot1_pos = "0";
        else
            bot1_pos = parse_position(bot1_attack_pos);
        if (bot2_attack_pos == 0)
            bot2_pos = "0";
        else
            bot2_pos = parse_position(bot2_attack_pos);
        
        std::cout << "Player 1 last attack: " << bot1_pos;
        if (bot1_last_hit)
            std::cout << "  HIT - Ships Left: " << bot2.getShips_left();
        else
            std::cout << "  MISS - Ships Left: " << bot2.getShips_left();
        std::cout << "      " << "Player 2 last attack: " << bot2_pos;
        if (bot2_last_hit)
            std::cout << "  HIT - Ships Left: " << bot1.getShips_left();
        else
        std::cout << "  MISS - Ships Left: " << bot1.getShips_left();
        std::cout << std::endl;
    }
    
    if (game_over)
    {
        if (bot2.isDefeated())
        {
            std::cout << "                                           PLAYER 1 WON                                             " << std::endl;
            std::cout << "                                     PRESS ENTER TO CONTINUE                                      " << std::endl;
        }
        else if (bot1.isDefeated())
        {
            std::cout << "                                           PLAYER 2 WON                                             " << std::endl;
            std::cout << "                                     PRESS ENTER TO CONTINUE                                      " << std::endl;
        }
        else
            throw std::runtime_error("Game Over Error");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}


std::string Demo::parse_position(int position)
{
    if (char(48+position%10)== '0')
    {
        std::string s1(1,char(64+position/10));
        return s1 + "10";
    }
    std::string s1(1,char(65+position/10));
    char c = char(48+position%10);
    std::string s2(1,c);
    return s1+s2; 
}


void Demo::reset()
{
    bot1.reset_positions();
    bot1.reset();
    bot2.reset_positions();
    bot2.reset();
    bot1_ready = false;
    bot2_ready = false;
    game_over = false;
    bot1_attack_pos = 0;
    bot2_attack_pos = 0;
    bot2_turn =false;
}