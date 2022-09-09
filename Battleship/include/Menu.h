// Menu.h

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


#ifndef HEADERS_MENU_
#define HEADERS_MENU_

#include "Controller.h"
#include "State.h"


class Menu : public State
{
public:
    Menu(Menu& other) = delete;            // Singleton is not cloneable.
    void operator=(const Menu&) = delete;  // Singleton is not assignable.
    static Menu* getInstance(Controller*);            // Calls constructor if there is no instance created. Otherwise returns pointer to instance.

private:
    Menu(Controller*);
    void render() override;
    void update() override;
    //void printHeader();
    void printHelp();

private:
    static Menu* menu_;
    int option;
};


#endif /* HEADERS_MENU_ */