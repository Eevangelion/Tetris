
#include "button.h"
#include <../../SFML/Graphics.hpp>

Button::Button(sf::String pathToNormal, sf::String pathToClicked, sf::String words, sf::Vector2f location, sf::Vector2f size) 
{
    if (!(normalTexture.loadFromFile(pathToNormal))) {
        throw "Can't open image of normal button!";
    }
    normalSprite.setTexture(normalTexture);
    if (!(clickedTexture.loadFromFile(pathToClicked))) {
        throw "Can't open image of clicked button!";
    }
    clickedSprite.setTexture(clickedTexture);
    currentState = false;
    normalSprite.setScale(sf::Vector2f(size.x / normalSprite.getLocalBounds().width, size.y / normalSprite.getLocalBounds().height));
    normalSprite.setPosition(location);
    clickedSprite.setScale(sf::Vector2f(size.x / clickedSprite.getLocalBounds().width, size.y / clickedSprite.getLocalBounds().height));
    clickedSprite.setPosition(location);
    currentSprite = &normalSprite;
    if (!(font.loadFromFile("fonts/Papernotes.ttf"))) {
        throw "Can't open font!";
    }
    text.setFont(font);
    text.setString(words);
    text.setCharacterSize(size.y / 2);
    text.setPosition(location.x + (size.x - text.getLocalBounds().width) / 2, location.y + 3 * size.y / 16);
    text.setFillColor(sf::Color(0, 0, 100));
}

Button::Button() {}

bool Button::checkMove(sf::Vector2f mouseCoord) 
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
    return currentState;
}

void Button::setState(bool newState) {
    currentState = newState;
    if (newState) {
        currentSprite = &clickedSprite;
        return;
    }
    currentSprite = &normalSprite;
}

bool Button::getState() {
    return currentState;
}

sf::Sprite Button::getSprite() {
    return *currentSprite;
}

sf::Text Button::getText() {
    return text;
}

Button::~Button() {}