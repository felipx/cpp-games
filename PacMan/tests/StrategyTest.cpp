
#include <iostream>
#include "Ghost.hpp"
#include "PacMan.hpp"
#include "Map.hpp"
#include "Strategy.hpp"
#include "Scatter.hpp"

int main()
{
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating Window\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	std::cout << "Creating PacMan\n";
	Ghost ghost(GhostName::Blinky, 16, "../media/images/Ghost", 100, &pacman, &map);
	std::cout << "Creating Ghost\n";
	ghost.setStrategy(new Scatter(&ghost, &map));
	std::cout << "Change Strategy\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));

	if (typeid(*ghost.getStrategy()).hash_code() != typeid(Scatter).hash_code()) {
		std::cout << "Change Strategy incorrect\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return -1;
	}
	else {
		std::cout << "Change Strategy correct\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 0;
	}


}