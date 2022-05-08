#pragma once
#include <../../SFML/Graphics.hpp>
class Tetromino {
protected:
    sf::Sprite* tetrominoBlocks;
    sf::Vector2i* coordinates;
    sf::Texture textureBlock;
    sf::Vector2f centerLocation;
    sf::Vector2f blockSize;
    short typeOfRotate;
    short typeOfTetromino;
    double speed;
    const double maxSpeed = 2.0;
public:
    Tetromino() : speed(1.0), typeOfRotate(0) {}
    Tetromino(sf::Vector2f, sf::Vector2f, short);
    void rotate();
    void speedUp(); 
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    sf::Vector2i* getCoordinates();
    sf::Sprite* getSpriteBlocks();
    ~Tetromino() {}
};