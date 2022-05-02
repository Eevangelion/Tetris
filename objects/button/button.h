#pragma once
#include <../../SFML/Graphics.hpp>

class Button {
    sf::Sprite normalSprite;
    sf::Sprite clickedSprite;
    sf::Sprite *currentSprite; 
    sf::Text text;
    bool currentState; // false if normal, true if clicked
public:
    Button(sf::String, sf::String, sf::String, sf::Vector2f);
    void checkClick(sf::Vector2f);
    void setState(bool);
    sf::Sprite* getSprite();
    sf::Text* getText();
    //~Button();
};
