#include <SFML/Graphics.hpp>
#include "screen/mainMenu.cpp"
#include "screen/gameScreen.cpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tetris");
    window.setVerticalSyncEnabled(true);
    int typeOfScreen = 0; // 0 - main menu, 1 - game screen, 2 - pause screen
    MainMenu mainMenu(window.getSize());
    while (window.isOpen()) 
    {
        if (typeOfScreen == 0) {
            sf::Event event;
            while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed) 
                    window.close();
                else if (event.type == sf::Event::MouseMoved) 
                    mainMenu.checkMouseMove(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (mainMenu.getStateOfButton(3)) {
                        window.close();
                    }
                }
            }
            mainMenu.refreshMainMenuScreen(window);
            window.display();
        }
    }
    return 0;
}