// GameController.hpp

#ifndef INCLUDE_GAMECONTROLLER_ 
#define INCLUDE_GAMECONTROLLER_

#include "Game.hpp"
#include "Menu.hpp"
#include "Publisher.hpp"
#include "State.hpp"

class GameController
{
public:
	GameController(GameController& other) = delete;
	void operator=(const GameController&) = delete;
	static GameController* createGameController(int, int);
	void setDifficulty(int);
	void setPlayer(std::string);
	void setState(State*);
	int getDifficulty();
	std::string getPlayer();
	void init();
	void standBy();
	void run();
private:
	GameController(int, int);
	void setTimePerFrame(float t);
private:
	static GameController* gameController_;
	Publisher* publisher;
	State* state;
	sf::RenderWindow mWindow;
	sf::Clock clock;
	sf::Time timePerFrame;
	int entityTileSize;
	int mapTileSize;
	int difficulty;
	std::string player{""};
};

#endif /* INCLUDE_GAMECONTROLLER_ */
