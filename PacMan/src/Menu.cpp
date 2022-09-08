// Menu.cpp

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

#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include "Menu.hpp"

Menu* Menu::menu_{ nullptr };

Menu::Menu(GameController* controller, Publisher* publisher, sf::RenderWindow* mWindow)
	: pacmanImage(), imageUpdateTime(sf::seconds(0.07f)),
	selection(0), imageCoord(0), numWindow(0), numScores(3), difficulty(1)
{
	setController(controller);
	setPublisher(publisher);
	setWindow(mWindow);
	setTitles();
	setOptions();
	loadScores();

	pacmanImage.setTileSize(16);
	if (!pacmanImage.loadImage("../media/images/Pacman16.png"))
		throw std::runtime_error("Failed to load Image ");
	pacmanImage.setPosition(120.f, 220.f);
}


Menu* Menu::createMenu(GameController* controller, Publisher* publisher, sf::RenderWindow* mWindow)
{
	if (menu_ == nullptr)
	{
		menu_ = new Menu(controller, publisher, mWindow);
	}
	return menu_;
}


void Menu::loadScores()
{
	std::fstream file;
	std::string name;
	std::string score;
	file.open("../scores.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	int i = 0;
	while (file >> name >> score)
	{
		scores[i] = (sf::Text());
		scores[i].setFont(*getMenuFont());
		scores[i].setString(name + " " + score);
		scores[i].setCharacterSize(10);
		scores[i].setPosition(sf::Vector2f(150.f, 220.f + i * 40.f));
		scores[i].setFillColor(sf::Color::Yellow);
		i++;
	}
	file.close();
}


void Menu::loginWindow()
{
	sf::String playerInput;
	sf::Text playerText;
	playerText.setFont(*getMenuFont());
	playerText.setCharacterSize(10);
	playerText.setPosition(sf::Vector2f(55.f, 40.f));
	playerText.setFillColor(sf::Color::Yellow);
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	logWindow.create(sf::VideoMode(250, 75), "Login Window");
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (logWindow.isOpen())
	{
		processLoginEvents(&playerInput, &playerText);
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processLoginEvents(&playerInput, &playerText);
		}
		logWindow.clear();
		logWindow.draw(opts[5]);
		logWindow.draw(playerText);
		logWindow.display();
	}
}


void Menu::processLoginEvents(sf::String* playerInput, sf::Text* playerText)
{
	sf::Event event{};
	while (logWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			logWindow.close();
			break;
		case sf::Event::TextEntered:
			if (event.text.unicode == '\b')
			{
				if (playerInput->getSize() > 0)
				{
					playerInput->erase(playerInput->getSize() - 1, 1);;
					playerText->setString(*playerInput);
				}
			}
			else if (event.text.unicode == '\r')
			{
				getController()->setPlayer(*playerInput);
				std::this_thread::sleep_for(std::chrono::milliseconds(75));
				logWindow.close();
				getPublisher()->notify(*playerInput);
			}
			else
			{
				if (playerInput->getSize() < 10)
				{
					*playerInput += event.text.unicode;
					playerText->setString(*playerInput);
				}
			}
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				logWindow.close();
			break;
		default:
			break;
		}
	}
}


void Menu::refreshImage()
{
	pacmanImage.setQuadTextureCoords((float)imageCoord, 0.f);
}


void Menu::render()
{
	if (numWindow == 0)
	{
		getWindow()->clear();
		getWindow()->draw(pacmanImage);
		getWindow()->draw(titles[0]);
		getWindow()->draw(opts[0]);
		getWindow()->draw(opts[1]);
		getWindow()->draw(opts[2]);
		getWindow()->draw(opts[3]);
		getWindow()->draw(opts[4]);
		getWindow()->display();
	}
	else if ((numWindow == 1))
	{
		getWindow()->clear();
		getWindow()->draw(titles[1]);
		for (sf::Text i : scores)
		{
			getWindow()->draw(i);
		}
		getWindow()->display();
	}
	else
	{
		getWindow()->clear();
		getWindow()->draw(opts[6]);
		getWindow()->draw(opts[7]);
		getWindow()->display();
	}
}


void Menu::setTitles()
{
	int i;
	for (i = 0; i < 2; i++)
	{
		titles[i].setFont(*getTitleFont());
		titles[i].setFillColor(sf::Color::Yellow);
		titles[i].setStyle(sf::Text::Bold);
	}
	titles[0].setString("PAC MAN");
	titles[0].setCharacterSize(50);
	titles[0].setPosition(sf::Vector2f(70.f, 100.f));
	titles[1].setString("HIGH SCORES");
	titles[1].setCharacterSize(40);
	titles[1].setPosition(sf::Vector2f(45.f, 100.f));
}


void Menu::setOptions()
{
	int i;
	float dy = 0;
	for (i = 0; i < 8; i++)
	{
		opts[i].setFont(*getMenuFont());
		opts[i].setCharacterSize(15);
		opts[i].setPosition(sf::Vector2f(150.f, 220.f + dy));
		opts[i].setFillColor(sf::Color::Yellow);
		switch (i)
		{
		case 0:
			opts[i].setString("new game");
			break;
		case 1:
			opts[i].setString("scores");
			break;
		case 2:
			opts[i].setString("config");
			break;
		case 3:
			opts[i].setString("login");
			break;
		case 4:
			opts[i].setString("exit");
			break;
		case 5:
			opts[i].setString("enter name");
			break;
		case 6:
			opts[i].setString("difficulty");
			break;
		case 7:
			opts[i].setString("normal");
			break;
		}
		dy += 40.f;
	}
	opts[5].setCharacterSize(10);
	opts[5].setPosition(sf::Vector2f(55.f, 3.f));
	opts[6].setCharacterSize(14);
	opts[6].setPosition(sf::Vector2f(80.f, 220.f));
	opts[7].setCharacterSize(12);
	opts[7].setPosition(sf::Vector2f(250.f, 220.f));
}


void Menu::update(sf::Time deltaTime)
{
	if (numWindow == 0)
	{
		refreshImage();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			pacmanImage.move(0.f, -40.f);
			selection--;
			if (selection < 0)
				selection = 4;
			if (pacmanImage.getPosition()[0].position.y < 220.f)
				pacmanImage.setPosition(120.f, 380.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			pacmanImage.move(0.f, 40.f);
			selection++;
			if (selection > 4)
				selection = 0;
			if (pacmanImage.getPosition()[0].position.y > 380.f)
				pacmanImage.setPosition(120.f, 220.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (selection == 0)
				getController()->standBy();
			if (selection == 1)
			{
				numWindow = 1;
				loadScores();
			}
			if (selection == 2)
			{
				numWindow = 2;
			}
			if (selection == 3)
			{
				loginWindow();
			}
			if (selection == 4)
			{
				getWindow()->close();
			}
		}
		updateImageCoord();
	}
	else if ((numWindow == 1))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			numWindow = 0;
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			getController()->setDifficulty(difficulty);
			numWindow = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			numWindow = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			difficulty++;
			if (difficulty > 2)
				difficulty = 0;
			switch (difficulty)
			{
			case 0:
				opts[7].setString("easy");
				break;
			case 1:
				opts[7].setString("normal");
				break;
			case 2:
				opts[7].setString("hard");
				break;
			default:
				break;
			}
		}
	}

}


void Menu::updateImageCoord()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= imageUpdateTime.asSeconds())
	{
		imageCoord += 16;
		if (imageCoord > (16 * 5))
			imageCoord = 0;
		clock.restart();
	}
}


sf::Text Menu::getTitle(int i)
{
	return titles[i];
}

sf::Text Menu::getOpt(int i)
{
	return opts[i];
}

Entity Menu::getPacmanImage()
{
	return pacmanImage;
}