// Controller.cpp

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


#include <typeinfo>
#include "Controller.h"


Controller* Controller::controller_{ nullptr };


Controller::Controller() : exit(false) {}


Controller::~Controller()
{
    State* s = state;
    standBy();
    delete s;
    delete state;
}


Controller* Controller::getInstance()
{
	if (controller_ == nullptr)
		controller_ = new Controller();
	return controller_;
}


void Controller::setState(State* s)
{
	state = s;
}


void Controller::setExit(bool e)
{
	exit = e;
}


void Controller::init()
{
	state = Menu::getInstance(this);
}


void Controller::standBy()
{
	if (typeid(Menu).hash_code() == typeid(*state).hash_code())
	{
		state = Game::getInstance(this);
	}
	else if (typeid(Game).hash_code() == typeid(*state).hash_code())
	{
		state = Menu::getInstance(this);
	}
}


void Controller::run()
{
    while (!exit)
    {
		state->render();
	    state->update();
    }
}