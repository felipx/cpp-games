// State.cpp

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
