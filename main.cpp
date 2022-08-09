#include <SFML/Graphics.hpp>
#include "screen/screen.h"
#include "screen/mainMenu.cpp"
#include "screen/gameScreen.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tetris");
    window.setVerticalSyncEnabled(true);
    Screen* screen = new MainMenu(window.getSize());
    bool screenMode = 0; // 0 - main, 1 - game
    GameScreen* lastGame = nullptr;
    while (window.isOpen()) 
    {
        screen->refreshScreen(window);
        window.display();
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) 
                window.close();
            else if (event.type == sf::Event::MouseMoved) 
                screen->checkMouseMove(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::String command = screen->checkClickedButtons();
                if (screenMode == 0 && command == "Start new game") {
                    screen = new GameScreen(window.getSize());
                    screenMode = 1;
                }
                else if (screenMode == 0 && command == "Resume") {
                    if (lastGame) {
                        screen = std::move(lastGame);
                        screenMode = 1;
                    }
                }
                else if (screenMode == 0 && command == "Exit") {
                    window.close();
                }
                else if (screenMode == 1 && command == "Pause") {
                    static_cast<GameScreen*>(screen)->changeStateOfPause();
                }
                else if (screenMode == 1 && command == "Unpause") {
                    static_cast<GameScreen*>(screen)->changeStateOfPause();
                }
                else if (screenMode == 1 && command == "Back to main menu") {
                    // need to save data of game
                    lastGame = std::move(static_cast<GameScreen*>(screen));
                    screen = new MainMenu(window.getSize());
                    screenMode = 0;
                }
            }
            if (screenMode == 1) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    static_cast<GameScreen*>(screen)->speedUp();
                else 
                    static_cast<GameScreen*>(screen)->speedDown();
            } 
            if (screenMode == 1 && event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                static_cast<GameScreen*>(screen)->moveTetrominoLeft();
            }
            else if (screenMode == 1 && event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                static_cast<GameScreen*>(screen)->moveTetrominoRight();
            }
            if (screenMode == 1 && event.type == sf::Event::KeyPressed && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
                static_cast<GameScreen*>(screen)->rotateTetromino();
        }
    }
    return 0;
}