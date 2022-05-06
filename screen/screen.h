#pragma once
class Screen {
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Vector2u resolution;
public:
    Screen() {}
    virtual void refreshScreen(sf::RenderWindow&) = 0;
    virtual void checkMouseMove(sf::Vector2f) = 0;
    virtual short checkMouseClick(sf::Vector2f) = 0;
    virtual bool getStateOfButton(short) = 0;
    virtual sf::String checkClickedButtons() = 0;
    ~Screen() {}
};