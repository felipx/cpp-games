
#include <iostream>
#include <chrono>
#include <thread>
#include "PacMan.hpp"
#include "Map.hpp"


int main()
{
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating PacMan\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	pacman.refreshImage();
	std::cout << "PacMan Creation succeded\n";
	

	pacman.setPosition(180.f, 270.f);
	pacman.setVelocity(pacman.getSpeed(), 0);
	sf::VertexArray array = pacman.getPosition();
	pacman.movePacman(sf::seconds(0.07f));
	//pacman.printPosition();
	if (array[0].position.x == pacman.getPosition()[0].position.x) {
		throw std::runtime_error("Failed to move Pacman ");
	}
	
	
	pacman.setPosition(180.f, 270.f);
	pacman.setVelocity(-pacman.getSpeed(), 0);
	array = pacman.getPosition();
	pacman.movePacman(sf::seconds(0.07f));
	if (array[0].position.x == pacman.getPosition()[0].position.x) {
		throw std::runtime_error("Failed to move Pacman ");
	}

	pacman.setPosition(180.f, 270.f);
	pacman.setVelocity(0, pacman.getSpeed());
	array = pacman.getPosition();
	pacman.movePacman(sf::seconds(0.07f));
	if (array[0].position.y == pacman.getPosition()[0].position.y) {
		throw std::runtime_error("Failed to move Pacman ");
	}


	pacman.setPosition(180.f, 270.f);
	pacman.setVelocity(0, -pacman.getSpeed());
	array = pacman.getPosition();
	pacman.movePacman(sf::seconds(0.07f));
	if (array[0].position.y == pacman.getPosition()[0].position.y) {
		throw std::runtime_error("Failed to move Pacman ");
	}

	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));

}
