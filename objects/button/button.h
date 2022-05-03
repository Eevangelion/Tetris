#pragma once
#include <../../SFML/Graphics.hpp>

class Button {
    sf::Texture normalTexture;
    sf::Sprite normalSprite;
    sf::Texture clickedTexture;
    sf::Sprite clickedSprite;
    sf::Sprite *currentSprite; 
    sf::Text text;
    sf::Font font;
    bool currentState; // false if normal, true if clicked
public:
    Button(sf::String, sf::String, sf::String, sf::Vector2f);
    Button();
    bool checkMove(sf::Vector2f);
    void setState(bool);
    bool getState();
    sf::Sprite getSprite();
    sf::Text getText();
    ~Button();
};