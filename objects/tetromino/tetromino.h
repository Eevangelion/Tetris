#pragma once
#include <../../SFML/Graphics.hpp>
class Tetromino {
protected:
    sf::Sprite tetrominoSprite;
    double speed;
    const double maxSpeed;
public:
    Tetromino() : speed(0.0), maxSpeed(2.0) {}
    virtual void rotate() = 0;
    virtual void speedUp() = 0; 
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    ~Tetromino() {}
};