
#include <iostream>
#include <chrono>
#include <thread>
#include "Map.hpp"
#include "PacMan.hpp"
#include "Ghost.hpp"


int main()
{

	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating Ghost\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	Ghost blinky(GhostName::Blinky, 16, "../media/images/Ghost", 100, &pacman, &map);
	blinky.refreshImage(0);
	std::cout << "Ghost Creation succeded\n";


	blinky.setPosition(180.f, 270.f);
	sf::VertexArray array = blinky.getPosition();
	//blinky.setVelocity(blinky.getSpeed(), 0);
	//blinky.update(0,sf::Time 50);
	//blinky.move(sf::Vector2f(100.f, 0));
	blinky.move(100.f, 0);
	blinky.printPosition();
	if (array[0].position.x == blinky.getPosition()[0].position.x) {
		throw std::runtime_error("Failed to move Ghost ");
	}

	blinky.setPosition(180.f, 270.f);
	array = blinky.getPosition();
	blinky.move(-100.f, 0);
	blinky.printPosition();
	if (array[0].position.x == blinky.getPosition()[0].position.x) {
		throw std::runtime_error("Failed to move Ghost ");
	}

	blinky.setPosition(180.f, 270.f);
	array = blinky.getPosition();
	blinky.move(0,100.f);
	blinky.printPosition();
	if (array[0].position.y == blinky.getPosition()[0].position.y) {
		throw std::runtime_error("Failed to move Ghost ");
	}

	blinky.setPosition(180.f, 270.f);
	array = blinky.getPosition();
	blinky.move(0,-100.f);
	blinky.printPosition();
	if (array[0].position.y == blinky.getPosition()[0].position.y) {
		throw std::runtime_error("Failed to move Ghost ");
	}

	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));

}