#include <SFML/Graphics.hpp>
#include "screen/screen.h"
#include "screen/mainMenu.cpp"
#include "screen/gameScreen.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tetris");
    window.setVerticalSyncEnabled(true);
    Screen* screen = new MainMenu(window.getSize());
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
                if (command == "Start new game") {
                    screen = new GameScreen(window.getSize());
                }
                else if (command == "Exit") {
                    window.close();
                }
                else if (command == "Pause") {
                    static_cast<GameScreen*>(screen)->changeStateOfPause();
                }
                else if (command == "Unpause") {
                    static_cast<GameScreen*>(screen)->changeStateOfPause();
                }
                else if (command == "Back to main menu") {
                    // need to save data of game
                    screen = new MainMenu(window.getSize());
                }
            }
            else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
                static_cast<GameScreen*>(screen)->moveTetrominoLeft();
            else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
                static_cast<GameScreen*>(screen)->moveTetrominoRight();
            else if (event.type == sf::Event::KeyPressed && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
                static_cast<GameScreen*>(screen)->rotateTetromino();
        }
    }
    return 0;
}