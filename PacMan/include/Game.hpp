// Game.hpp

#ifndef INCLUDE_GAME_
#define INCLUDE_GAME_

#include "SFML/Graphics.hpp"
#include "Dots.hpp"
#include "Frightened.hpp"
#include "GameController.hpp"
#include "Ghost.hpp"
#include "Map.hpp"
#include "PacMan.hpp"
#include "Publisher.hpp"
#include "Scatter.hpp"
#include "State.hpp"

class Game : public State
{
public:
	Game(Game& other) = delete;
	void operator=(const Game&) = delete;
	static Game* createGame(GameController*, Publisher*,sf::RenderWindow*, int, int, int);
private:
	Game(GameController*, Publisher*, sf::RenderWindow*, int, int, int);
	void setDifficulty(int);
	void loadHighScore();
	void processScores();
	void render() override;
	void resetGame();
	void update(sf::Time) override;
private:
	static Game* game_;
	PacMan pacman;
	Ghost blinky;
	Ghost pinky;
	Ghost inky;
	Ghost clyde;
	Map map;
	Dots dots;
	int actScore;
	int hScore;
	int dotsLeft;
	int energizersLeft;
	int scatterLeft;
	int lifes;
	bool gameWon;
	bool restart;
	bool onFrighten;
	bool onScatter;
	sf::Clock clock;
	sf::Clock frightenClock;
	sf::Clock scatterClock;
	sf::Text highScore;
	sf::Text winText;
	sf::Text actualScore;
	sf::Texture lifeImage;
	sf::Sprite lifeSprite;
};

#endif /* INCLUDE_GAME_ */