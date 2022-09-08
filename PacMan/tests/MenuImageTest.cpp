#include <iostream>
#include <chrono>
#include <thread>
#include "GameController.hpp"
#include "Menu.hpp"
#include "Publisher.hpp"


int main()
{
	int mapTileSize = 16;
	int entityTileSize = 16;

	std::cout << "Creating Window\n";
	sf::RenderWindow mWindow(sf::VideoMode(448, 608), "Test");
	std::cout << "Window Creation succeded\n";
	std::cout << "Creating GameController\n";

	//GameController* controller = GameController::createGameController(mapTileSize, entityTileSize);
	Publisher* publisher = Publisher::createPublisher();
	Menu* menu = Menu::createMenu(nullptr, publisher, &mWindow);
	
	int i = 3;
	while (i > 0)
	{
		sf::Event event;
		mWindow.pollEvent(event);

		Entity pacmanImage = menu->getPacmanImage();
		pacmanImage.setQuadTextureCoords(0, 0);

		menu->getWindow()->clear();
		menu->getWindow()->draw(pacmanImage);
		menu->getWindow()->draw(menu->getTitle(0));
		menu->getWindow()->draw(menu->getOpt(0));
		menu->getWindow()->draw(menu->getOpt(1));
		menu->getWindow()->draw(menu->getOpt(2));
		menu->getWindow()->display();

		std::this_thread::sleep_for(std::chrono::seconds(1));
		i--;
	}

	std::cout << "Closing window\n";
	mWindow.close();
	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
}
