// Menu.cpp

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
#include "Menu.h"

#ifdef _WIN32
//#define clrscr() std::cout <<"\033[H\033[2J\033[3J"
#else
#define clrscr() std::cout <<"\033[H\033[2J\033[3J"
#endif


Menu* Menu::menu_{ nullptr };


Menu::Menu(Controller* controller) : State(controller), option(1) {}


Menu* Menu::getInstance(Controller* controller)
{
    if (menu_ == nullptr)
    {
        menu_ = new Menu(controller);
    }
    return menu_;
}


void Menu::update()
{
    std::cin >> option;
    if ( std::cin.fail() ) {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (option == 1)
        getController()->standBy(0);
    if (option == 2)
        getController()->standBy(1);
    if (option == 4)
        getController()->setExit(true);
}


void Menu::render()
{
    clrscr();
    printHeader();
    std::cout << "\n\n"
              << "felipx\n"
              << "https://github.com/felipx\n"
              << "\n\n\n\n";
    if (option < 1 || option > 4)
        std::cout << "Invalid Answer.\n"
                  << "Select an option:\n" << "1) New Game\n2) demo\n3) Help\n4) Exit\n";
    else
        std::cout << "\nSelect an option:\n" << "1) New Game\n2) demo\n3) Help\n4) Exit\n";
}


void Menu::printHelp() {}
