// Menu.hpp

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

#ifndef INCLUDE_MENU_
#define INCLUDE_MENU_

#include <array>
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include "GameController.hpp"
#include "Publisher.hpp"
#include "State.hpp"

class Menu : public State
{
public:
    Menu(Menu& other) = delete;
    void operator=(const Menu&) = delete;
    static Menu* createMenu(GameController*, Publisher*, sf::RenderWindow*);
    sf::Text getTitle(int);
    sf::Text getOpt(int);
    Entity getPacmanImage();
private:
    Menu(GameController*, Publisher*, sf::RenderWindow*);
    void loadScores();
    void loginWindow();
    void processLoginEvents(sf::String*, sf::Text*);
    void setTitles();
    void setOptions();
    void refreshImage();
    void render() override;
    void update(sf::Time) override;
    void updateImageCoord();
private:
    static Menu* menu_;
    int difficulty;
    int selection;
    int numWindow;
    int numScores;
    int imageCoord;
    Entity pacmanImage;
    sf::Clock clock;
    sf::Time imageUpdateTime;
    sf::RenderWindow logWindow;
    std::array<sf::Text, 2> titles;
    std::array<sf::Text, 8> opts;
    std::array<sf::Text, 5> scores;

};

#endif /* INCLUDE_MENU_ */