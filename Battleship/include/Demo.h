// Demo.h

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


#ifndef HEADERS_DEMO_
#define HEADERS_DEMO_

#include <string>
#include "Bot.h"
#include "Controller.h"
#include "Player.h"
#include "State.h"


class Demo : public State
{
public:
    Demo(Demo& other) = delete;             // Singleton is not cloneable.
    void operator=(const Demo&) = delete;   // Singleton is not assignable.
    static Demo* getInstance(Controller*);  // Calls constructor if there is no instance created. Otherwise returns pointer to instance.   
private:
    Demo(Controller*);
    void render() override;
    void update() override;
    std::string parse_position(int);
    void reset();
private:
    static Demo* demo_;
    Bot bot1;
    Bot bot2;
    bool bot1_ready;
    bool bot2_ready;
    int bot1_attack_pos;
    int bot2_attack_pos;
    bool bot1_last_hit;
    bool bot2_last_hit;
    bool bot2_turn;
    bool game_over;
};


#endif /* HEADERS_DEMO_ */