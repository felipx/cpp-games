// main.cpp

#include "GameController.hpp"

int main()
{
	int mapTileSize = 16;
	int entityTileSize = 16;
	GameController* controller = GameController::createGameController(mapTileSize, entityTileSize);
	controller->init();
	controller->run();
}



