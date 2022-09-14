// Game.h

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


#ifndef HEADERS_GAME_
#define HEADERS_GAME_

#include <string>
#include "Bot.h"
#include "Controller.h"
#include "Player.h"
#include "State.h"


class Game : public State
{
public:
    Game(Game& other) = delete;             // Singleton is not cloneable.
    void operator=(const Game&) = delete;   // Singleton is not assignable.
    static Game* getInstance(Controller*);  // Calls constructor if there is no instance created. Otherwise returns pointer to instance.   
private:
    Game(Controller*);
    void render() override;
    void update() override;
    std::string parse_position(int);
    void reset();
private:
    static Game* game_;
    Bot bot;
    Player player;
    bool bot_ready;
    bool player_ready;
    bool invalid_answer;
    int bot_attack_pos;
    int player_attack_pos;
    bool bot_last_hit;
    bool player_last_hit;
    bool bot_turn;
    bool game_over;
};


#endif /* HEADERS_GAME_ */