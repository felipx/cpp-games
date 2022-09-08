// Game.cpp

#include <array>
#include <chrono>
#include <fstream>
#include <thread>
#include "Game.hpp"

Game* Game::game_{ nullptr };

Game::Game(GameController* controller, Publisher* publisher, sf::RenderWindow* mWindow, int entityTileSize, int mapTileSize, int difficulty)
	: map("../media/images/Map", sf::Vector2u(mapTileSize, mapTileSize), 28, 36),
	dots(level, 28, 36),
	pacman(entityTileSize, "../media/images/Pacman", 100, &map),
	blinky(GhostName::Blinky, entityTileSize, "../media/images/Ghost", 190, &pacman, &map),
	pinky(GhostName::Pinky, entityTileSize, "../media/images/Ghost", 100, &pacman, &map),
	inky(GhostName::Inky, entityTileSize, "../media/images/Ghost", 100, &pacman, &map),
	clyde(GhostName::Clyde, entityTileSize, "../media/images/Ghost", 100, &pacman, &map),
	actScore(0), dotsLeft(dots.getNumDots()), energizersLeft(dots.getNumEnergizers()),
	gameWon(false), restart(true), scatterLeft(4), onFrighten(false), onScatter(false),
	lifes(3)
{
	if (!lifeImage.loadFromFile("../media/images/Pacman16.png"))
		throw std::runtime_error("Failed to load lifeImage");
	lifeSprite.setTexture(lifeImage);
	lifeSprite.setTextureRect(sf::IntRect(entityTileSize*2, entityTileSize*2, entityTileSize, entityTileSize));
	lifeSprite.setPosition(50.f, 550.f);
	setController(controller);
	setPublisher(publisher);
	setWindow(mWindow);
	loadHighScore();
	actualScore.setFont(*getMenuFont());
	actualScore.setCharacterSize(8);
	actualScore.setPosition(sf::Vector2f(250.f, 30.f));
	actualScore.setFillColor(sf::Color::Yellow);
	setDifficulty(difficulty);
}


Game* Game::createGame(GameController* controller, Publisher* publisher, sf::RenderWindow* mWindow, int entityTileSize, int mapTileSize, int difficulty)
{
	if (game_ == nullptr)
	{
		game_ = new Game(controller, publisher, mWindow, entityTileSize, mapTileSize, difficulty);
	}
	return game_;
}


void Game::setDifficulty(int d)
{
	switch (d)
	{
	case 0:
		blinky.setSpeed(185);
		pinky.setSpeed(80);
		inky.setSpeed(80);
		clyde.setSpeed(80);
		break;
	case 1:
		blinky.setSpeed(190);
		pinky.setSpeed(100);
		inky.setSpeed(100);
		clyde.setSpeed(100);
		break;
	case 2:
		blinky.setSpeed(230);
		pinky.setSpeed(170);
		inky.setSpeed(170);
		clyde.setSpeed(170);
		break;
	default:
		break;
	}
}


void Game::loadHighScore()
{
	std::fstream file;
	std::string name;
	std::string score;
	file.open("../scores.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	file >> name >> score;
	highScore.setFont(*getMenuFont());
	highScore.setString("high score " + score);
	highScore.setCharacterSize(8);
	highScore.setPosition(sf::Vector2f(10.f, 30.f));
	highScore.setFillColor(sf::Color::Yellow);
	try {
		hScore = std::stoi(score);
	}
	catch (const std::exception& e)
	{
		(void)e;
		hScore = 0;
	}
	file.close();
}


void Game::processScores()
{
	std::array<std::string, 5> names{""};
	std::array<int, 5> scores{0};
	std::fstream file;
	std::string name;
	std::string score;
	file.open("../scores.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	int i,j,s, numScores = 0;
	bool empty = true;
	i = 0;
	while(file >> name >> score)
	{
		empty = false;
		numScores++;
		if (!name.empty())
		    names[i] = name;
		try {
			s = std::stoi(score);
			scores[i] = s;
		}
		catch (const std::exception& e)
		{
			(void)e;
			s = 0;
		}
	i++;
	}
	file.close();
	if (empty)
	{
		if (!getController()->getPlayer().empty())
			names[0] = getController()->getPlayer();
		else
			names[0] = "pacman";
		scores[0] = actScore;
	}
	else if (numScores == 5)
	{
		if (actScore >= scores[numScores - 1])
		{
			if (names[numScores - 1].compare("pacman") && names[numScores - 1].compare(getController()->getPlayer()))
				getPublisher()->addSubscriber(names[numScores - 1]);
			if (!getController()->getPlayer().empty())
				names[numScores - 1] = getController()->getPlayer();
			else
				names[numScores - 1] = "pacman";
			scores[numScores - 1] = actScore;
		}
	}
	else
	{
		if (!getController()->getPlayer().empty())
			names[numScores] = getController()->getPlayer();
		else
			names[numScores] = "pacman";
		scores[numScores] = actScore;
		numScores++;
	}
	for (i = 0; i < numScores - 1; i++) {
		for (j = 0; j < numScores - i - 1; j++) {
			if (scores[j] < scores[j + 1]) {
				int tempScore = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = tempScore;
				std::string tempName = names[j];
				names[j] = names[j + 1];
				names[j + 1] = tempName;
			}
		}
	}
	file.open("../scores.txt", std::fstream::in | std::fstream::out | std::ofstream::trunc);
	for (i = 0; i < 5; i++)
	{
		if (!names[i].empty() && scores[i] != 0)
		    file << names[i] << " " << scores[i] << "\n";
	}
	file.close();
}


void Game::render()
{
	if (lifes <= 0)
	{
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock deadclock;
		sf::Clock innerClock;
		sf::Time dyingTime = sf::Time::Zero;
		int i = 0;
		float x = pacman.getPosition()[0].position.x;
		float y = pacman.getPosition()[0].position.y;
		pacman.setSpritePosition(x, y);
		deadclock.restart();
		while (dyingTime.asSeconds() < 2)
		{
			//state->processEvents();
			timeSinceLastUpdate += innerClock.restart();
			while (timeSinceLastUpdate > sf::seconds(10.f / 60.f))
			{
				timeSinceLastUpdate -= sf::seconds(10.f / 60.f);
				pacman.updateSprite(i);
				i += 16;
				if (i > pacman.getTileSize() * 11)
				{
					i = 0;
					break;
				}
			}
			getWindow()->clear();
			getWindow()->draw(pacman.getSprite());
			getWindow()->display();
			
			dyingTime = deadclock.getElapsedTime();
		}
	}
	else
	{
		if (!gameWon)
		{
			int i;
			getWindow()->clear();
			getWindow()->draw(map);
			getWindow()->draw(highScore);
			getWindow()->draw(actualScore);
			int numDots = dots.getNumDots();
			for (i = 0; i < numDots; i++)
			{
				if (dots.getDotsPtr()[i] != nullptr)
					getWindow()->draw(*dots.getDotsPtr()[i]);
			}
			int numEnergizers = dots.getNumEnergizers();
			for (i = 0; i < numEnergizers; i++)
			{
				if (dots.getEnergizersPtr()[i] != nullptr)
					getWindow()->draw(*dots.getEnergizersPtr()[i]);
			}
			getWindow()->draw(pacman);
			getWindow()->draw(blinky);
			getWindow()->draw(pinky);
			getWindow()->draw(inky);
			getWindow()->draw(clyde);
			for (i = 1; i <= lifes; i++)
			{
				getWindow()->draw(lifeSprite);
				lifeSprite.setPosition(50.f + i*30.f, 550.f);
			}
			getWindow()->display();
			lifeSprite.setPosition(50.f, 550.f);
		}
		if (gameWon)
		{
			int i;
			getWindow()->clear();
			getWindow()->draw(map);
			getWindow()->draw(highScore);
			getWindow()->draw(actualScore);
			getWindow()->draw(pacman);
			getWindow()->draw(blinky);
			getWindow()->draw(pinky);
			getWindow()->draw(inky);
			getWindow()->draw(clyde);
			for (i = 1; i <= lifes; i++)
			{
				getWindow()->draw(lifeSprite);
				lifeSprite.setPosition(50.f + i * 30.f, 550.f);
			}
			getWindow()->display();
			lifeSprite.setPosition(50.f, 550.f);

		}
	}
}


void Game::resetGame()
{
	gameWon = false;
	pacman.setPosition(50.f, 65.f);
	dots.resetPtrs();
	actScore = 0;
	scatterLeft = 4;
	lifes = 3;
	dotsLeft = dots.getNumDots();
	energizersLeft = dots.getNumEnergizers();
	getController()->setPlayer("");

	blinky.setPosition(180.f, 270.f);
	pinky.setPosition(200.f, 270.f);
	inky.setPosition(230.f, 270.f);
	clyde.setPosition(250.f, 270.f);

	if (blinky.isEaten())
		blinky.setEaten();
	if (pinky.isEaten())
		pinky.setEaten();
	if (inky.isEaten())
		inky.setEaten();
	if (clyde.isEaten())
		clyde.setEaten();

	loadHighScore();
	restart = true;
	
}


void Game::update(sf::Time deltaTime)
{
	if (lifes <= 0)
		{
		processScores();
		resetGame();
		getController()->standBy();
		return;
		}
	else
	{
		if (restart)
		{
			restart = false;
			blinky.setPosition(180.f, 270.f);
			pinky.setPosition(200.f, 270.f);
			inky.setPosition(230.f, 270.f);
			clyde.setPosition(250.f, 270.f);
			pacman.setPosition(50.f, 65.f);
			clock.restart();
		}
		if (!gameWon)
		{
			sf::Time elapsed = clock.getElapsedTime();
			if (elapsed.asMilliseconds() < 350)
			{
				blinky.update(0, deltaTime);
				blinky.move(sf::Vector2f(100.f, 0) * deltaTime.asSeconds());
				pinky.update(0, deltaTime);
				pinky.move(sf::Vector2f(50.f, 0) * deltaTime.asSeconds());
				inky.update(0, deltaTime);
				inky.move(sf::Vector2f(-50.f, 0) * deltaTime.asSeconds());
				clyde.update(0, deltaTime);
				clyde.move(sf::Vector2f(-100.f, 0) * deltaTime.asSeconds());
			}
			else if (elapsed.asMilliseconds() >= 350 && elapsed.asMilliseconds() < 800)
			{
				blinky.update(0, deltaTime);
				blinky.move(sf::Vector2f(0.f, -100.f) * deltaTime.asSeconds());
				pinky.update(0, deltaTime);
				pinky.move(sf::Vector2f(0.f, -100.f) * deltaTime.asSeconds());
				inky.update(0, deltaTime);
				inky.move(sf::Vector2f(0.f, -100.f) * deltaTime.asSeconds());
				clyde.update(0, deltaTime);
				clyde.move(sf::Vector2f(0.f, -100.f) * deltaTime.asSeconds());
			}
			else
			{
				blinky.getStrategy()->act(deltaTime);
				pinky.getStrategy()->act(deltaTime);
				clyde.getStrategy()->act(deltaTime);
				inky.getStrategy()->act(deltaTime);
			}

			if (scatterLeft > 0 && !onFrighten)
			{
				sf::Time scatterTime = scatterClock.getElapsedTime();
				if (scatterTime.asSeconds() > 20)
				{
					if (!onScatter)
					{
						blinky.setStrategy(new Scatter(&blinky, &map));
						pinky.setStrategy(new Scatter(&pinky, &map));
						inky.setStrategy(new Scatter(&inky, &map));
						clyde.setStrategy(new Scatter(&clyde, &map));
						onScatter = true;
					}
					else
					{
						if (scatterTime.asSeconds() > 24)
						{
							blinky.setStrategy(new Chase(&blinky, &pacman, &map));
							pinky.setStrategy(new Chase(&pinky, &pacman, &map));
							inky.setStrategy(new Chase(&inky, &pacman, &map));
							clyde.setStrategy(new Chase(&clyde, &pacman, &map));
							scatterLeft--;
							onScatter = false;
							scatterClock.restart();
						}
					}
				}
			}

			if (onFrighten)
			{
				sf::Time frightenTime = frightenClock.getElapsedTime();
				if (frightenTime.asSeconds() > 5)
				{
					blinky.setStrategy(new Chase(&blinky, &pacman, &map));
					pinky.setStrategy(new Chase(&pinky, &pacman, &map));
					inky.setStrategy(new Chase(&inky, &pacman, &map));
					clyde.setStrategy(new Chase(&clyde, &pacman, &map));
					if (blinky.isEaten())
						blinky.setEaten();
					if (pinky.isEaten())
						pinky.setEaten();
					if (inky.isEaten())
						inky.setEaten();
					if (clyde.isEaten())
						clyde.setEaten();
					onFrighten = false;
					frightenClock.restart();
				}
			}

			pacman.refreshImage();
			pacman.movePacman(deltaTime);
			int i;
			int numDots = dots.getNumDots();
			if (dotsLeft > 0)
			{
				for (i = 0; i < numDots; i++)
				{
					if (dots.getDotsPtr()[i] != nullptr)
					{
						if (pacman.detectCollision(dots.getDotsPtr()[i]->getPosition().x, dots.getDotsPtr()[i]->getPosition().y))
						{
							dots.nullDotPtr(i);
							actScore += 10;
							dotsLeft--;
							if (dotsLeft <= 0)
								break;
						}
					}
				}
			}
			int numEnergizers = dots.getNumEnergizers();
			if (energizersLeft > 0)
			{
				for (i = 0; i < numEnergizers; i++)
				{
					if (dots.getEnergizersPtr()[i] != nullptr)
					{
						if (pacman.detectCollision(dots.getEnergizersPtr()[i]->getPosition().x, dots.getEnergizersPtr()[i]->getPosition().y))
						{
							dots.nullEnergizerPtr(i);
							actScore += 50;
							energizersLeft--;
							frightenClock.restart();
							onFrighten = true;
							blinky.setStrategy(new Frightened(&blinky, &map));
							pinky.setStrategy(new Frightened(&pinky, &map));
							inky.setStrategy(new Frightened(&inky, &map));
							clyde.setStrategy(new Frightened(&clyde, &map));
							if (energizersLeft <= 0)
								break;
						}
					}
				}
			}
			if (blinky.detectCollision(pacman.getPosition()[0].position.x, pacman.getPosition()[0].position.y))
			{
				if (!onFrighten)
				{
					lifes--;
					restart = true;
					onFrighten = false;
					std::this_thread::sleep_for(std::chrono::milliseconds(75));
					return;
				}
				else
				{
					if (!blinky.isEaten())
					{
						blinky.setEaten();
						actScore += 350;
					}
				}
			}
			if (pinky.detectCollision(pacman.getPosition()[0].position.x, pacman.getPosition()[0].position.y))
			{
				if (!onFrighten)
				{
					lifes--;
					restart = true;
					onFrighten = false;
					std::this_thread::sleep_for(std::chrono::milliseconds(75));
					return;
				}
				else
				{
					if (!pinky.isEaten())
					{
						pinky.setEaten();
						actScore += 300;
					}
				}
			}
			if (inky.detectCollision(pacman.getPosition()[0].position.x, pacman.getPosition()[0].position.y))
			{
				if (!onFrighten)
				{
					lifes--;
					restart = true;
					onFrighten = false;
					std::this_thread::sleep_for(std::chrono::milliseconds(75));
					return;
				}
				else
				{
					if (!inky.isEaten())
					{
						inky.setEaten();
						actScore += 300;
					}
				}
			}
			if (clyde.detectCollision(pacman.getPosition()[0].position.x, pacman.getPosition()[0].position.y))
			{
				if (!onFrighten)
				{
					lifes--;
					restart = true;
					onFrighten = false;
					std::this_thread::sleep_for(std::chrono::milliseconds(75));
					return;
				}
				else
				{
					if (!clyde.isEaten())
					{
						clyde.setEaten();
						actScore += 300;
					}
				}
			}

			if (dotsLeft <= 0 && energizersLeft <= 0)
				gameWon = true;
			actualScore.setString("score: " + std::to_string(actScore));

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				resetGame();
				getController()->standBy();
			}
		}
		if (gameWon)
		{
			processScores();
			std::this_thread::sleep_for(std::chrono::seconds(3));
			resetGame();
			getController()->standBy();
		}
	}

}
