
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "PacMan.hpp"
#include "Map.hpp"
			

int main (){

	std::cout << "Creating map\n";
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "map created\n";
	std::cout << "Creating PacMan\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	std::cout << "pacman created\n";
	
	pacman.setPosition(12.3f, 65.f);
	pacman.setVelocity(-pacman.getSpeed(), 0);
	float px = pacman.getPosition()[0].position.x;
	float py = pacman.getPosition()[0].position.y;
	std::cout << std::setprecision(3) << "pacman position original: (" << px << ";" << py << ")" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	for (int i = 0; i < 10; i++)
	{
		pacman.movePacman(sf::seconds(1.f / 60.f));
		pacman.movePacman(sf::seconds(1.f / 60.f));
		pacman.movePacman(sf::seconds(1.f / 60.f));
		pacman.movePacman(sf::seconds(1.f / 60.f));
		pacman.movePacman(sf::seconds(1.f / 60.f));
		pacman.movePacman(sf::seconds(1.f / 60.f));
	}

	std::cout << "pacman position new: (" << pacman.getPosition()[0].position.x << ";" << pacman.getPosition()[0].position.y << ")" << std::endl;

		if (pacman.getPosition()[0].position.x == px && pacman.getPosition()[0].position.y == py) {
			std::cout << "Test Passed\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			return 0;
			std::cout << "PacMan wall Test succeded\n";
		}
		else {
			std::cout << "Test not Passed\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));

			return -1; 
		}


}