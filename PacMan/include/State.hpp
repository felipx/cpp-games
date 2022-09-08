// State.hpp

#ifndef INCLUDE_STATE_
#define INCLUDE_STATE_

#include "SFML/Graphics.hpp"
#include "Publisher.hpp"

class GameController;

class State
{
public:
    State();
    void setWindow(sf::RenderWindow*);
    void setController(GameController*);
    void setPublisher(Publisher*);
    GameController* getController();
    sf::Font* getMenuFont();
    Publisher* getPublisher();
    sf::Font* getTitleFont();
    sf::RenderWindow* getWindow();
    bool loadMenuFont(const std::string&);
    bool loadTitleFont(const std::string&);
    void processEvents();
    virtual void render();
    virtual void update(sf::Time);
private:
    GameController* controller;
    Publisher* publisher;
    sf::RenderWindow* mWindow;
    sf::Font titleFont;
    sf::Font menuFont;
};

#endif /* INCLUDE_STATE_ */
