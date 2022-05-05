#include "../objects/button/button.h"
#include "screen.h"
#include <../SFML/Graphics.hpp>


class GameScreen : public Screen {
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Vector2u resolution;
    Button* pauseButton;
    Button* unpauseButton;
    sf::Sprite pauseSprite;
    sf::Texture pauseTexture;
    bool pauseState;
public:
    GameScreen(sf::Vector2u screenResolution) {
        resolution = screenResolution;
        pauseButton = new Button(sf::String("models/button/buttonNormal.png"), sf::String("models/button/buttonClicked.png"), sf::String("PAUSE"), sf::Vector2f(resolution.x / 3., resolution.y / 2.));
        unpauseButton = new Button(sf::String("models/button/buttonNormal.png"), sf::String("models/button/buttonClicked.png"), sf::String("RETURN"), sf::Vector2f(resolution.x / 3., resolution.y / 2.));
        backgroundTexture.loadFromFile("models/screens/mainMenuScreen.jpg");
        backgroundSprite = sf::Sprite(backgroundTexture);
        pauseTexture.loadFromFile("models/screens/pause.jpg");
        pauseSprite = sf::Sprite(pauseTexture);
        pauseSprite.setPosition((resolution.x - pauseSprite.getGlobalBounds().width) / 2, (resolution.y - pauseSprite.getGlobalBounds().height) / 2);
        pauseState = false;
    }
    void refreshScreen(sf::RenderWindow&);
    void checkMouseMove(sf::Vector2f);
    short checkMouseClick(sf::Vector2f);
    bool getStateOfButton(short);
    sf::String checkClickedButtons();
    void changeStateOfPause();
    ~GameScreen() {}
};

void GameScreen::refreshScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    // Background
    window.draw(backgroundSprite);

    // Button pause game
    window.draw(pauseButton->getSprite());
    window.draw(pauseButton->getText());

    // Pause sprite if paused
    if (pauseState == true) {
        window.draw(pauseSprite);
        window.draw(unpauseButton->getSprite());
        window.draw(unpauseButton->getText());
    }

}
void GameScreen::checkMouseMove(sf::Vector2f mouseCoord) {
    if (pauseState == false)
        pauseButton->checkMove(mouseCoord);
    else 
        unpauseButton->checkMove(mouseCoord);
}

short GameScreen::checkMouseClick(sf::Vector2f mouseCoord) {
    if (pauseState == false) {
        if (pauseButton->checkMove(mouseCoord)) 
            return 0;
    }
    else {
        if (unpauseButton->checkMove(mouseCoord)) 
            return 1;
    }
    return 5;
}

bool GameScreen::getStateOfButton(short type) {
    switch (type) {
    case 0: 
        return !pauseState && pauseButton->getState();
        break;
    case 1:
        return pauseState && unpauseButton->getState();
    default:
        return false;
        break;
    }
}


sf::String GameScreen::checkClickedButtons() {
    if (pauseButton->getState())
    {
        return "Pause";
    }
    if (unpauseButton->getState()) 
    {
        return "Unpause";
    }
    return "Do nothing";
}

void GameScreen::changeStateOfPause() {
    pauseState = !pauseState;
}