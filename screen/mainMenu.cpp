#include "../objects/button/button.h"
#include <../SFML/Graphics.hpp>

class MainMenu {
    Button* exitButton, *startNewGameButton, *resumeGameButton, *recordsButton;    
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Text screenTitle;
    sf::Font fontTitle;
    sf::Vector2u resolution;
public:
    MainMenu(sf::Vector2u screenResolution) {
        resolution = screenResolution;
        startNewGameButton = new Button(sf::String("models/button/buttonNormal.png"), sf::String("models/button/buttonClicked.png"), sf::String("START NEW GAME"), sf::Vector2f(resolution.x / 3., resolution.y / 2.));
        resumeGameButton = new Button(sf::String("models/button/buttonNormal.png"), sf::String("models/button/buttonClicked.png"), sf::String("RESUME GAME"), sf::Vector2f(resolution.x / 3., 5. * resolution.y / 8));
        recordsButton = new Button(sf::String("models/button/buttonNormal.png"), sf::String("models/button/buttonClicked.png"), sf::String("RECORDS"), sf::Vector2f(resolution.x / 3., 6. * resolution.y / 8));
        exitButton = new Button(sf::String("models/button/buttonNormal.png"), sf::String("models/button/buttonClicked.png"), sf::String("EXIT GAME"), sf::Vector2f(resolution.x / 3., 7. * resolution.y / 8));
        backgroundTexture.loadFromFile("models/screens/mainMenuScreen.jpg");
        backgroundSprite = sf::Sprite(backgroundTexture);
        fontTitle.loadFromFile("fonts/Papernotes Bold.ttf");
        screenTitle.setString("Tetris");
        screenTitle.setFont(fontTitle);
        screenTitle.setCharacterSize(resolution.y / 8.);
        screenTitle.setFillColor(sf::Color::Black);
        screenTitle.setPosition((resolution.x - screenTitle.getGlobalBounds().width) / 2., resolution.y / 10.);
    }

    void refreshMainMenuScreen(sf::RenderWindow&);
    void checkMouseMove(sf::Vector2f);
    short checkMouseClick(sf::Vector2f);
    void resize(sf::Vector2u);
    bool getStateOfButton(short);
};

void MainMenu::refreshMainMenuScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    // Background
    window.draw(backgroundSprite);

    // Title
    window.draw(screenTitle);

    // Button start new game
    window.draw(startNewGameButton->getSprite());
    window.draw(startNewGameButton->getText());

    // Button resume game
    window.draw(resumeGameButton->getSprite());
    window.draw(resumeGameButton->getText());

    // Button records
    window.draw(recordsButton->getSprite());
    window.draw(recordsButton->getText());

    // Button exit game
    window.draw(exitButton->getSprite());
    window.draw(exitButton->getText());
}
void MainMenu::checkMouseMove(sf::Vector2f mouseCoord) {
    startNewGameButton->checkMove(mouseCoord);
    resumeGameButton->checkMove(mouseCoord);
    recordsButton->checkMove(mouseCoord);
    exitButton->checkMove(mouseCoord);
}

short MainMenu::checkMouseClick(sf::Vector2f mouseCoord) {
    if (exitButton->checkMove(mouseCoord)) 
        return 3;
    return 5;
}

bool MainMenu::getStateOfButton(short type) {
    switch (type) {
    case 0: 
        return startNewGameButton->getState();
        break;
    case 1:
        return resumeGameButton->getState();
        break;
    case 2:
        return recordsButton->getState();
        break;
    case 3:
        return exitButton->getState();
        break;
    default:
        return false;
        break;
    }
}
