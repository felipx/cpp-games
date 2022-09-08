
#include <fstream>
#include <iostream>
#include "Game.hpp"
#include "PacMan.hpp"
#include "GameController.hpp"
#include "Menu.hpp"


int main() {

	int mapTileSize = 16;
	int entityTileSize = 16;
	GameController* controller = GameController::createGameController(mapTileSize, entityTileSize);
	controller->init();
	controller->run();
	sf::RenderWindow mWindow(sf::VideoMode(448, 608), "Test");


	std::ifstream archivo;


	archivo.open("../out/build/sx64-debug/scoressss.txt", std::ifstream::in);


		if (archivo.fail()) {

			std::cout << "Ema gato";

			exit(1);

	}



	std::cout << "Closing window\n";
	mWindow.close();
	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
}
