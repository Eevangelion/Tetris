#include <../SFML/Graphics.hpp>
#include "../objects/button/button.cpp"

class MainMenu {
    Button* exitButton, *startNewGameButton, *resumeGameButton, *recordsButton;    
public:
    MainMenu() {
        startNewGameButton = new Button(sf::String("models/button/abobanormal.png"), sf::String("models/button/abobaclicked.png"), sf::String("New game"), sf::Vector2f(400., 200.));
        resumeGameButton = new Button(sf::String("models/button/abobanormal.png"), sf::String("models/button/abobaclicked.png"), sf::String("Resume game"), sf::Vector2f(400., 325.));
        recordsButton = new Button(sf::String("models/button/abobanormal.png"), sf::String("models/button/abobaclicked.png"), sf::String("Records"), sf::Vector2f(400., 450.));
        exitButton = new Button(sf::String("models/button/abobanormal.png"), sf::String("models/button/abobaclicked.png"), sf::String("Exit game"), sf::Vector2f(400., 575.));
        
    }

    void refreshMainMenuScreen(sf::RenderWindow&);
    void checkMouse(sf::Vector2f);
};

void MainMenu::refreshMainMenuScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
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
void MainMenu::checkMouse(sf::Vector2f mouseCoord) {
    startNewGameButton->checkClick(mouseCoord);
    resumeGameButton->checkClick(mouseCoord);
    recordsButton->checkClick(mouseCoord);
    exitButton->checkClick(mouseCoord);

}