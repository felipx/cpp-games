// State.cpp

/***********************************************************************************
 * This file is part of PacMan game                                                *
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

#include "State.hpp"

State::State()
{
	if (!loadTitleFont("../media/fonts/pac-font.ttf"))
		throw std::runtime_error("Failed to load font pac-font.ttf");
	if (!loadMenuFont("../media/fonts/namco.ttf"))
		throw std::runtime_error("Failed to load font namco.ttf");
}


void State::setController(GameController* c)
{
	controller = c;
}


void State::setPublisher(Publisher* p)
{
	publisher = p;
}


void State::setWindow(sf::RenderWindow* w)
{
	mWindow = w;
}


GameController* State::getController()
{
	return controller;
}


sf::Font* State::getMenuFont()
{
	return &menuFont;
}


Publisher* State::getPublisher()
{
	return publisher;
}


sf::Font* State::getTitleFont()
{
	return &titleFont;
}


sf::RenderWindow* State::getWindow()
{
	return mWindow;
}


bool State::loadMenuFont(const std::string& filename)
{
	if (!menuFont.loadFromFile(filename))
		throw std::runtime_error("Failed to load menu font");
	return true;
}


bool State::loadTitleFont(const std::string& filename)
{
	if (!titleFont.loadFromFile(filename))
		throw std::runtime_error("Failed to load title font");
	return true;
}


void State::processEvents()
{
	sf::Event event{};
	while (mWindow->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow->close();
			break;
		default:
			break;
		}
	}
}


void State::render()
{
}


void State::update(sf::Time)
{
}
