#include <../../SFML/Graphics.hpp>
//#include "button.h"

class Button {
    sf::Texture normalTexture;
    sf::Sprite normalSprite;
    sf::Texture clickedTexture;
    sf::Sprite clickedSprite;
    sf::Sprite *currentSprite; 
    sf::Text text;
    sf::Font font;
    bool currentState; // false if normal, true if clicked
    friend class MainMenu;
public:
    Button(sf::String, sf::String, sf::String, sf::Vector2f);
    Button();
    void checkClick(sf::Vector2f);
    void setState(bool);
    sf::Sprite getSprite();
    sf::Text getText();
    //~Button();
};

Button::Button(sf::String pathToNormal, sf::String pathToClicked, sf::String words, sf::Vector2f location) 
{
    if (!(this->normalTexture.loadFromFile(pathToNormal))) {
        throw "Can't open image of normal button!";
    }
    this->normalSprite.setTexture(normalTexture);
    if (!(this->clickedTexture.loadFromFile(pathToClicked))) {
        throw "Can't open image of clicked button!";
    }
    this->clickedSprite.setTexture(clickedTexture);
    this->currentState = false;
    this->normalSprite.setPosition(location);
    this->clickedSprite.setPosition(location);
    this->currentSprite = &normalSprite;
    if (!(this->font.loadFromFile("fonts/Papernotes.ttf"))) {
        throw "Can't open font!";
    }
    this->text.setFont(font);
    this->text.setString(words);
    this->text.setCharacterSize(50);
    this->text.setPosition(location.x + 25, location.y + 25);
    this->text.setFillColor(sf::Color::Red);
}

Button::Button() {}

void Button::checkClick(sf::Vector2f mouseCoord) 
{
    if (mouseCoord.x > currentSprite->getPosition().x && mouseCoord.x < (currentSprite->getPosition().x + currentSprite->getGlobalBounds().width)) 
    {
        if (mouseCoord.y > currentSprite->getPosition().y && mouseCoord.y < (currentSprite->getPosition().y + currentSprite->getGlobalBounds().height)) 
        {
            setState(true);
        }
        else {
            setState(false);
        }
    }   
    else {
        setState(false);
    }
}

void Button::setState(bool newState) {
    currentState = newState;
    if (newState) {
        currentSprite = &clickedSprite;
        return;
    }
    currentSprite = &normalSprite;
}

sf::Sprite Button::getSprite() {
    return *currentSprite;
}

sf::Text Button::getText() {
    return text;
}
