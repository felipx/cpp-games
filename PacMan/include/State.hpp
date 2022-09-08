// State.hpp

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

#ifndef INCLUDE_STATE_
#define INCLUDE_STATE_

#include "SFML/Graphics.hpp"
#include "Publisher.hpp"

class GameController;

class State
{
public:
    State();
    void setWindow(sf::RenderWindow*);
    void setController(GameController*);
    void setPublisher(Publisher*);
    GameController* getController();
    sf::Font* getMenuFont();
    Publisher* getPublisher();
    sf::Font* getTitleFont();
    sf::RenderWindow* getWindow();
    bool loadMenuFont(const std::string&);
    bool loadTitleFont(const std::string&);
    void processEvents();
    virtual void render();
    virtual void update(sf::Time);
private:
    GameController* controller;
    Publisher* publisher;
    sf::RenderWindow* mWindow;
    sf::Font titleFont;
    sf::Font menuFont;
};

#endif /* INCLUDE_STATE_ */
