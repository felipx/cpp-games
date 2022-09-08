// Menu.hpp

#ifndef INCLUDE_MENU_
#define INCLUDE_MENU_

#include <array>
#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include "GameController.hpp"
#include "Publisher.hpp"
#include "State.hpp"

class Menu : public State
{
public:
    Menu(Menu& other) = delete;
    void operator=(const Menu&) = delete;
    static Menu* createMenu(GameController*, Publisher*, sf::RenderWindow*);
    sf::Text getTitle(int);
    sf::Text getOpt(int);
    Entity getPacmanImage();
private:
    Menu(GameController*, Publisher*, sf::RenderWindow*);
    void loadScores();
    void loginWindow();
    void processLoginEvents(sf::String*, sf::Text*);
    void setTitles();
    void setOptions();
    void refreshImage();
    void render() override;
    void update(sf::Time) override;
    void updateImageCoord();
private:
    static Menu* menu_;
    int difficulty;
    int selection;
    int numWindow;
    int numScores;
    int imageCoord;
    Entity pacmanImage;
    sf::Clock clock;
    sf::Time imageUpdateTime;
    sf::RenderWindow logWindow;
    std::array<sf::Text, 2> titles;
    std::array<sf::Text, 8> opts;
    std::array<sf::Text, 5> scores;

};

#endif /* INCLUDE_MENU_ */