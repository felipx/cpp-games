
#include <iostream>
#include "Ghost.hpp"
#include "PacMan.hpp"
#include "Map.hpp"
#include "Strategy.hpp"
#include "Entity.hpp"

int main()
{
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating Window\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	std::cout << "Creating PacMan\n";
	int right = RIGHT;
	pacman.setDirection(right);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	if (pacman.getDirection() == right)
	{
		std::cout << "Correct direction\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return 0;
	}
	else
	{
		std::cout << "Incorrect direction\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return -1;
	}

}