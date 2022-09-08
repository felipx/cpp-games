
#include <iostream>
#include <chrono>
#include <thread>
#include "Ghost.hpp"
#include "PacMan.hpp"
#include "Map.hpp"

int main()
{
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating Window\n";
	sf::RenderWindow mWindow(sf::VideoMode(448, 608), "Test");
	std::cout << "Window Creation succeded\n";
	std::cout << "Creating Ghosts\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	Ghost blinky(GhostName::Blinky, 16, "../media/images/Ghost", 100, &pacman, &map);
	Ghost pinky(GhostName::Pinky, 16, "../media/images/Ghost", 100, &pacman, &map);
	Ghost inky(GhostName::Inky, 16, "../media/images/Ghost", 100, &pacman, &map);
	Ghost clyde(GhostName::Clyde, 16, "../media/images/Ghost", 100, &pacman, &map);
	blinky.refreshImage(0);
	pinky.refreshImage(0);
	inky.refreshImage(0);
	clyde.refreshImage(0);

	int i = 3;
	while (i > 0)
	{
		sf::Event event;
		mWindow.pollEvent(event);
		mWindow.clear();
		mWindow.draw(blinky);
		mWindow.draw(pinky);
		mWindow.draw(inky);
		mWindow.draw(clyde);
		mWindow.display();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		i--;
	}
	std::cout << "Closing window\n";
	mWindow.close();
	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));

}