#include "tetromino.h"
#include <../../SFML/Graphics.hpp>

class Tetromino { // ....
    sf::RectangleShape tetrominoBlock1;
    sf::RectangleShape tetrominoBlock2;
    sf::RectangleShape tetrominoBlock3;
    sf::RectangleShape tetrominoBlock4;
    sf::Texture textureBlock;
    sf::Vector2f topLeftCoord;
    sf::Vector2f blockSize;
    short typeOfRotate;
    double speed;
    const double maxSpeed = 2.0;
public:
    Tetromino() {}
    Tetromino(sf::Vector2f location, sf::Vector2f sizeOfBlock) {
        speed = 1.0;
        typeOfRotate = 0;
        blockSize = sizeOfBlock;
        textureBlock.create(sizeOfBlock.x, sizeOfBlock.y);
        tetrominoBlock1.setTexture(&textureBlock);
        tetrominoBlock2.setTexture(&textureBlock);
        tetrominoBlock3.setTexture(&textureBlock);
        tetrominoBlock4.setTexture(&textureBlock);
        topLeftCoord = location;
    }
    void rotate();
    void speedUp();
    void moveLeft();
    void moveRight();


    ~Tetromino();
};


    void Tetromino::rotate() {
        typeOfRotate = (typeOfRotate + 1) % 4;
    }
    void Tetromino::speedUp() {
        speed = std::min(speed + 0.05, maxSpeed);
    }
    void Tetromino::moveLeft() {
        topLeftCoord.x -= blockSize.x;
    }
    void Tetromino::moveRight() {
        topLeftCoord.x += blockSize.y;
    }