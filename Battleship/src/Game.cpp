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

//debug
#include <chrono>
#include <thread>
//debug

#ifdef _WIN32
//#define clrscr() std::cout <<"\033[H\033[2J\033[3J"
#else
#define clrscr() std::cout <<"\033[H\033[2J\033[3J"
#endif


Game* Game::game_{ nullptr };


Game::Game(Controller* controller) : State(controller), player(), bot_ready(false), player_ready(false), invalid_answer(false), 
                                     bot_attack_pos(0), player_attack_pos(0), bot_last_hit(false), player_last_hit(false), 
                                     bot_turn(false), game_over(false) {}


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
        invalid_answer = false;
        std::string str;
        std::getline(std::cin, str);
        if (str == "Exit" || str == "exit")
        {
            getController()->setExit(true);
            return;
        }
        if (str == "Menu" || str == "menu")
        {
            reset();
            getController()->standBy(0);
            return;
        }
        if (std::cin.fail() || str.size() < 5 || str.size() > 7)
        {
            std::cin.clear();
            invalid_answer = true;
            return;
        }
        if (player.set_ships(str))
            player.setShips_set();
        else
            invalid_answer = true;
        if (player.getShips_set() == 5)
        {
            player_ready = true;
            render();  // render call
        }
    }
    if (player_ready && bot_ready && !game_over)
    {
        // Player attack starts here
        invalid_answer = false;
        bot_turn = false;
        std::string str;
        std::cin >> str;
        if ( std::cin.fail() ) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (str == "Exit" || str == "exit")
        {
            getController()->setExit(true);
            return;
        }
        if (str == "Menu" || str == "menu")
        {
            reset();
            getController()->standBy(0);
            return;
        }
        int last_player_pos = player_attack_pos;
        player_attack_pos = player.parse_position(str);
        if (player_attack_pos != -1)
        {
            if (!player.fire(player_attack_pos))
            {
                invalid_answer = true;
                player_attack_pos = last_player_pos;
            }
            else
            {
                if (bot.respond(player_attack_pos))
                {
                    player.getAttacked_positions()[player_attack_pos-1] = 1;
                    player_last_hit = true;
                    if (bot.isDefeated())
                    {
                        game_over = true;
                        return;
                    }
                    render();
                }
                else
                {
                    player.getAttacked_positions()[player_attack_pos-1] = 2;
                    player_last_hit = false;
                    bot_turn = true;
                    render();
                }
            }
        }
        else
        {
            invalid_answer = true;
            player_attack_pos = last_player_pos;
            return;
        }

        // Bot attack starts here
        if (bot_turn)
        {
            if (!bot.getAttack_positions()->isStacked())
            {
                bot_attack_pos = bot.fire();
                bot.setLast_attack(bot_attack_pos);
                if (player.respond(bot_attack_pos))    
                {
                    bot.getAttacked_positions()[bot_attack_pos-1] = 1;
                    bot_last_hit = true;
                    bot.getAttack_positions()->stack_positions(bot_attack_pos);
                    if (player.isDefeated())
                    {
                    game_over = true;
                    return;
                    }
                    render(); // render call
                }
                else
                {
                    bot.getAttacked_positions()[bot_attack_pos-1] = 2;
                    bot_last_hit = false;
                    bot_turn = false;
                    return;
                }
            }
            bool firing = true;
            while (firing)
            {
                bot_attack_pos = bot.fire();
                if (player.respond(bot_attack_pos))
                {
                    bot.getAttacked_positions()[bot_attack_pos-1] = 1;
                    bot_last_hit = true;
                    if (player.isDefeated())
                    {
                        game_over = true;
                        return;
                    }
                    render(); // render call
                    bot.stack_next(bot_attack_pos);
                }
                else
                {
                    bot.getAttacked_positions()[bot_attack_pos-1] = 2;
                    bot_last_hit = false;
                    firing = false;
                    bot_turn = false;
                }
            }
        }
        bot_turn = false;
    }
    if (game_over)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string a;
        std::getline(std::cin, a);
        reset();
        getController()->standBy(0);
    }
}


void Game::render()
{
    int i, j, k;
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
                    bool set = false;
                    for (k=0; k<17; k++)
                    {
                        if (player.getPositions_set()[k] == i-58-3*j-(i/100)*90 && bot.getAttacked_positions()[i-59-3*j-(i/100)*90] == 0)
                        {
                            std::cout << "v";
                            set = true;
                            break;
                        }
                        if (player.getPositions_set()[k] == i-58-3*j-(i/100)*90 && bot.getAttacked_positions()[i-59-3*j-(i/100)*90] == 1)
                        {
                            std::cout << "x";
                            set = true;
                            break;
                        }
                    }
                    if (!set)
                    {
                        if (bot.getAttacked_positions()[i-59-3*j-(i/100)*90] == 2)
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
    std::cout << "   ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾                  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
    
    if (!player_ready)
    {
        int ships_set = player.getShips_set();
        switch (ships_set)
        {
        case 0:
            if (invalid_answer)
                std::cout << "Inalid Answer, try again!" << std::endl;
            else
                std::cout << std::endl;
            std::cout << "Select start and end positions for Carrier Ship (5 positions):" << std::endl;
            break;
        case 1:
            if (invalid_answer)
                std::cout << "Inalid Answer, try again!" << std::endl;
            else
                std::cout << std::endl;
            std::cout << "Select start and end positions for Battleship Ship (4 positions):" << std::endl;
            break;
        case 2:
            if (invalid_answer)
                std::cout << "Inalid Answer, try again!" << std::endl;
            else
                std::cout << std::endl;
            std::cout << "Select start and end positions for Cruiser Ship (3 positions):" << std::endl;
            break;
        case 3:
            if (invalid_answer)
                std::cout << "Inalid Answer, try again!" << std::endl;
            else
                std::cout << std::endl;
            std::cout << "Select start and end positions for Submarine (3 positions):" << std::endl;
            break;
        case 4:
            if (invalid_answer)
                std::cout << "Inalid Answer, try again!" << std::endl;
            else
                std::cout << std::endl;
            std::cout << "Select start and end positions for Destroyer Ship (2 positions):" << std::endl;
            break;
        default:
            throw std::runtime_error("Player Ships Initialization Error");
            break;
        }
    }
    
    if (player_ready && bot_ready && !game_over)
    {
        std::string player_pos;
        std::string bot_pos;
        if (player_attack_pos == 0)
            player_pos = "0";
        else
            player_pos = parse_position(player_attack_pos);
        if (bot_attack_pos == 0)
            bot_pos = "0";
        else
            bot_pos = parse_position(bot_attack_pos);
        
        std::cout << "Player last attack: " << player_pos;
        if (player_last_hit)
            std::cout << "  HIT - Ships Left: " << bot.getShips_left();
        else
            std::cout << "  MISS - Ships Left: " << bot.getShips_left();
        std::cout << "           " << "Enemy last attack: " << bot_pos;
        if (bot_last_hit)
            std::cout << "  HIT - Ships Left: " << player.getShips_left();
        else
        std::cout << "  MISS - Ships Left: " << player.getShips_left();
        std::cout << std::endl;
        if (!bot_turn)
        {
            if (invalid_answer)
                std::cout << "Inalid Answer, try again!" << std::endl;
            std::cout << "\nSelect Attack Position: " << std::endl;
        }
    }
    
    if (game_over)
    {
        if (player.isDefeated())
        {
            std::cout << "                                            YOU LOST                                                " << std::endl;
            std::cout << "                                     PRESS ENTER TO CONTINUE                                      " << std::endl;
        }
        else if (bot.isDefeated())
        {
            std::cout << "                                             YOU WON                                                " << std::endl;
            std::cout << "                                     PRESS ENTER TO CONTINUE                                      " << std::endl;
        }
        else
            throw std::runtime_error("Game Over Error");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}


std::string Game::parse_position(int position)
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


void Game::reset()
{
    bot.reset_positions();
    bot.reset();
    player.reset();
    bot_ready = false;
    player_ready = false;
    game_over = false;
    invalid_answer = false;
    bot_attack_pos = 0;
    player_attack_pos = 0;
}