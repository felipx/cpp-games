
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "PacMan.hpp"
#include "Ghost.hpp"
#include "Map.hpp"


int main() {

	Map map("../media/images/Map", sf::Vector2u(16, 16), 28, 36);
	PacMan pacman(16, "../media/images/Pacman", 100, &map);
	Ghost ghost(GhostName::Blinky, 16, "../media/images/Ghost", 100, &pacman, &map);

	ghost.setPosition(15.f, 65.f);
	ghost.setVelocity(-ghost.getSpeed(), 0);
	float px = ghost.getPosition()[0].position.x;
	float py = ghost.getPosition()[0].position.y;
	std::cout << std::setprecision(3) << "pacman position original: (" << px << ";" << py << ")" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	for (int i = 0; i < 100; i++)
	{
		ghost.move(-0.1f, 0.f);
		float px2 = ghost.getPosition()[0].position.x;
		float py2 = ghost.getPosition()[0].position.y;
		if (map.detectCollision(px2, py2)) {
			std::cout << "Test Passed\n";
			return 0;
		}
	}
	std::cout << "Test not Passed\n";
	return -1;

}