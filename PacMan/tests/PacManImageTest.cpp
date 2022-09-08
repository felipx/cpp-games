
#include <iostream>
#include <chrono>
#include <thread>
#include "PacMan.hpp"
#include "Map.hpp"

int main()
{
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "Creating Window\n";
	sf::RenderWindow mWindow(sf::VideoMode(448, 608), "Test");
	std::cout << "Window Creation succeded\n";
	std::cout << "Creating PacMan\n";
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	pacman.refreshImage();
	std::cout << "PacMan Creation succeded\n";
	int i = 3;
	while (i > 0)
	{
		sf::Event event;
		mWindow.pollEvent(event);
		mWindow.clear();
		mWindow.draw(pacman);
		mWindow.display();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		i--;
	}
	std::cout << "Closing window\n";
	mWindow.close();
	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	
}
