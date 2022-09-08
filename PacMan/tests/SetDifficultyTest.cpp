
#include <iostream>
#include "GameController.hpp"
#include "Menu.hpp"
#include "Publisher.hpp"
#include "State.hpp"


int main()
{
	int mapTileSize = 16;
	int entityTileSize = 16;
	GameController* controller = GameController::createGameController(mapTileSize, entityTileSize);

	controller->setDifficulty(2);
	int diff1 = controller->getDifficulty();

	controller->setDifficulty(0);
	int diff2 = controller->getDifficulty();

	if (diff1 != diff2) {
		std::cout << "Test Passed";
		return 0;
	}
	else {
		std::cout << "Test failed";
		return -1;
	}
	
}