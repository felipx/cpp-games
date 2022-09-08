
#include <iostream>
#include <chrono>
#include <thread>
#include "Map.hpp"
#include "PacMan.hpp"
#include "Ghost.hpp"

int main()
{
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating Pacman\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	std::cout << "Creating Ghost\n";
	Ghost blinky(GhostName::Blinky, 16, "../media/images/Ghost", 100, &pacman, &map);
	pacman.refreshImage();
	std::cout << "PacMan Creation succeded\n";
	blinky.refreshImage(0);
	std::cout << "Ghost Creation succeded\n";
	sf::VertexArray array;
	sf::VertexArray array2;

	
	

	pacman.setPosition(170.f, 270.f);
	blinky.setPosition(190.f, 270.f);
	pacman.setVelocity(pacman.getSpeed(), 0);
	pacman.movePacman(sf::seconds(0.10f));
	blinky.move(-10.f, 0);
	array  = pacman.getPosition();
	array2 = blinky.getPosition();
	pacman.printPosition();
	blinky.printPosition();
	if (array[0].position.x != array2[0].position.x) {
		throw std::runtime_error("Failed to move Pacman or Ghost");
	}

	pacman.setPosition(190.f, 270.f);
	blinky.setPosition(170.f, 270.f);
	pacman.setVelocity(-pacman.getSpeed(), 0);
	pacman.movePacman(sf::seconds(0.10f));
	blinky.move(10.f, 0);
	array = pacman.getPosition();
	array2 = blinky.getPosition();
	pacman.printPosition();
	blinky.printPosition();
	if (array[0].position.x != array2[0].position.x) {
		throw std::runtime_error("Failed to move Pacman or Ghost");
	}

	pacman.setPosition(180.f, 260.f);
	blinky.setPosition(180.f, 280.f);
	pacman.setVelocity(0, pacman.getSpeed());
	pacman.movePacman(sf::seconds(0.10f));
	blinky.move(0, -10.f);
	array = pacman.getPosition();
	array2 = blinky.getPosition();
	pacman.printPosition();
	blinky.printPosition();
	if (array[0].position.y != array2[0].position.y) {
		throw std::runtime_error("Failed to move Pacman or Ghost");
	}

	pacman.setPosition(180.f, 280.f);
	blinky.setPosition(180.f, 260.f);
	pacman.setVelocity(0, -pacman.getSpeed());
	pacman.movePacman(sf::seconds(0.10f));
	blinky.move(0, 10.f);
	array = pacman.getPosition();
	array2 = blinky.getPosition();
	pacman.printPosition();
	blinky.printPosition();
	if (array[0].position.y != array2[0].position.y) {
		throw std::runtime_error("Failed to move Pacman or Ghost");
	}

	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
}