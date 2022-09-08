
#include <iostream>
#include <chrono>
#include <thread>
#include "Map.hpp"

int main()
{
	std::cout << "Creating Window\n";
	sf::RenderWindow mWindow(sf::VideoMode(448, 608), "Test");
	std::cout << "Window Creation succeded\n";
	std::cout << "Creating map\n";
	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	std::cout << "map Creation succeded\n";
	int i = 3;
	while (i > 0)
	{
		sf::Event event;
		mWindow.pollEvent(event);
		mWindow.clear();
		mWindow.draw(map);
		mWindow.display();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		i--;
	}
	std::cout << "Closing window\n";
	mWindow.close();
	std::cout << "Test Passed\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
}