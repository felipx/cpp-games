
#include <iostream>
#include "Ghost.hpp"
#include "PacMan.hpp"
#include "Map.hpp"
#include "Strategy.hpp"
#include "Entity.hpp"
#include "Scatter.hpp"

int main()
{
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating Window\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	std::cout << "Creating PacMan\n";
	Ghost ghost(GhostName::Blinky, 16, "../media/images/Ghost", 100, &pacman, &map);
	std::cout << "Creating Ghost\n";
	int right = RIGHT;
	ghost.setDirection(right);
	std::cout << "Set direction\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));

	if (ghost.getDirection() == right)
	{
		std::cout << "Correct direction\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return 0;
	}else
	{
		std::cout << "Incorrect direction\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return -1;
	}

}