#include <SFML/Graphics.hpp>
#include "screen/mainMenu.cpp"
#include "screen/gameScreen.cpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tetris");
    int typeOfScreen = 0; // 0 - main menu, 1 - game screen, 2 - pause screen
    MainMenu mainMenu;
    while (window.isOpen()) 
    {
        if (typeOfScreen == 0) {
            sf::Event event;
            while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed) 
                    window.close();
                if (event.type == sf::Event::MouseMoved) 
                    mainMenu.checkMouse(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            }
            mainMenu.refreshMainMenuScreen(window);
            window.display();
        }
    }
    return 0;
}