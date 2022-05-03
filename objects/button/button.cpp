
#include "button.h"
#include <../../SFML/Graphics.hpp>

Button::Button(sf::String pathToNormal, sf::String pathToClicked, sf::String words, sf::Vector2f location) 
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
    normalSprite.setPosition(location);
    clickedSprite.setPosition(location);
    currentSprite = &normalSprite;
    if (!(font.loadFromFile("fonts/Papernotes.ttf"))) {
        throw "Can't open font!";
    }
    text.setFont(font);
    text.setString(words);
    text.setCharacterSize(currentSprite->getLocalBounds().height / 2);
    text.setPosition(location.x + (currentSprite->getLocalBounds().width - text.getLocalBounds().width) / 2, location.y + currentSprite->getLocalBounds().height / 4);
    text.setFillColor(sf::Color::Black);
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