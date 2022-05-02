#include <../SFML/Graphics.hpp>

void turnToGameScreen() {
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tetris");

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
                window.close();
        }
        window.clear(sf::Color::Black);
        
        window.display();
    }
}