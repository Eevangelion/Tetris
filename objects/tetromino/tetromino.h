#pragma once
#include <../../SFML/Graphics.hpp>
class Tetromino {
protected:
    sf::RectangleShape tetrominoBlock1;
    sf::RectangleShape tetrominoBlock2;
    sf::RectangleShape tetrominoBlock3;
    sf::RectangleShape tetrominoBlock4;
    sf::Texture textureBlock;
    sf::Vector2f topLeftCoord;
    short typeOfRotate;
    double speed;
    const double maxSpeed = 2.0;
public:
    Tetromino() : speed(1.0), typeOfRotate(0) {}
    virtual void rotate() = 0;
    virtual void speedUp() = 0; 
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    ~Tetromino() {}
};