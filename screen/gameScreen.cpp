#include "../objects/button/button.h"
#include "screen.h"
#include <../SFML/Graphics.hpp>


class GameScreen : public Screen {
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Vector2u resolution;
    Button* pauseButton, *unpauseButton, *backToMainMenuButton;
    sf::Sprite pauseSprite;
    sf::Texture pauseTexture;
    sf::Text pausedTitle;
    sf::Font fontPaused;
    bool pauseState;
public:
    GameScreen(sf::Vector2u screenResolution) {
        resolution = screenResolution;
        pauseButton = new Button(sf::String("models/button/buttonNormal.png"), 
                                sf::String("models/button/buttonClicked.png"), 
                                sf::String("PAUSE"), 
                                sf::Vector2f(0.85 * resolution.x, 0.88 * resolution.y), 
                                sf::Vector2f(0.15 * resolution.x, 0.12 * resolution.y));
        unpauseButton = new Button(sf::String("models/button/buttonNormal.png"), 
                                sf::String("models/button/buttonClicked.png"), 
                                sf::String("RETURN"), 
                                sf::Vector2f(2 * resolution.x / 5., resolution.y / 2.),
                                sf::Vector2f(resolution.x / 5., 1.5 * resolution.y / 16));
        backToMainMenuButton = new Button(sf::String("models/button/buttonNormal.png"),
                                sf::String("models/button/buttonClicked.png"),
                                sf::String("MAIN MENU"),
                                sf::Vector2f(2 * resolution.x / 5., 5 * resolution.y / 8.),
                                sf::Vector2f(resolution.x / 5., 1.5 * resolution.y / 16));
        backgroundTexture.loadFromFile("models/screens/mainMenuScreen.png");
        backgroundSprite = sf::Sprite(backgroundTexture);
        backgroundSprite.setScale(sf::Vector2f(resolution.x / backgroundSprite.getLocalBounds().width, resolution.y / backgroundSprite.getLocalBounds().height));
        pauseTexture.loadFromFile("models/screens/pause.png");
        pauseSprite = sf::Sprite(pauseTexture);
        pauseSprite.setScale(sf::Vector2f(3 / 7. * resolution.x / pauseSprite.getLocalBounds().width, 0.5 * resolution.y / pauseSprite.getLocalBounds().height));
        pauseSprite.setPosition((resolution.x - pauseSprite.getGlobalBounds().width) / 2, (resolution.y - pauseSprite.getGlobalBounds().height) / 2);
        pauseState = false;
        fontPaused.loadFromFile("fonts/UchronyRoman-Regular-FFP.ttf");
        pausedTitle.setString("Paused");
        pausedTitle.setFont(fontPaused);
        pausedTitle.setCharacterSize(resolution.y / 10.);
        pausedTitle.setFillColor(sf::Color::White);
        pausedTitle.setPosition((resolution.x - pausedTitle.getGlobalBounds().width) / 2., 2.5 * resolution.y / 8.);
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
        window.draw(backToMainMenuButton->getSprite());
        window.draw(backToMainMenuButton->getText());
        window.draw(pausedTitle);
    }

}
void GameScreen::checkMouseMove(sf::Vector2f mouseCoord) {
    if (pauseState == false)
        pauseButton->checkMove(mouseCoord);
    else {
        unpauseButton->checkMove(mouseCoord);
        backToMainMenuButton->checkMove(mouseCoord);
    }
}

short GameScreen::checkMouseClick(sf::Vector2f mouseCoord) {
    if (pauseState == false) {
        if (pauseButton->checkMove(mouseCoord)) 
            return 0;
    }
    else {
        if (unpauseButton->checkMove(mouseCoord)) 
            return 1;
        if (backToMainMenuButton->checkMove(mouseCoord)) 
            return 2;
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
    case 2:
        return pauseState && backToMainMenuButton->getState();
    default:
        return false;
        break;
    }
}


sf::String GameScreen::checkClickedButtons() {
    if (!pauseState && pauseButton->getState())
    {
        return "Pause";
    }
    if (pauseState && unpauseButton->getState()) 
    {
        return "Unpause";
    }
    if (pauseState && backToMainMenuButton->getState()) {
        return "Back to main menu";
    }
    return "Do nothing";
}

void GameScreen::changeStateOfPause() {
    pauseState = !pauseState;
    pauseButton->setState(false);
    unpauseButton->setState(false);
}