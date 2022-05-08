#include "tetromino.h"
#include <../../SFML/Graphics.hpp>

Tetromino::Tetromino(sf::Vector2f location, sf::Vector2f sizeOfBlock, short type) {
    typeOfTetromino = type;
    speed = 1.0;
    typeOfRotate = 0;
    blockSize = sizeOfBlock;
    textureBlock.loadFromFile("models/block/block.png");
    tetrominoBlocks = new sf::Sprite[4];
    coordinates = new sf::Vector2i[4];
    for (int i = 0; i < 4; ++i) {
        tetrominoBlocks[i].setTexture(textureBlock);
        tetrominoBlocks[i].setScale(sf::Vector2f(blockSize.x / tetrominoBlocks[i].getLocalBounds().width, blockSize.y / tetrominoBlocks[i].getLocalBounds().height));
    }
    if (type == 0) {
        coordinates[0] = sf::Vector2i(3, 0);
        coordinates[1] = sf::Vector2i(4, 0);
        coordinates[2] = sf::Vector2i(5, 0);
        coordinates[3] = sf::Vector2i(6, 0);
    }
    else if (type == 1) {
        coordinates[0] = sf::Vector2i(4, 1);
        coordinates[1] = sf::Vector2i(5, 1);
        coordinates[2] = sf::Vector2i(6, 1);
        coordinates[3] = sf::Vector2i(6, 0);
    }
    else if (type == 2) {
        coordinates[0] = sf::Vector2i(4, 1);
        coordinates[1] = sf::Vector2i(5, 1);
        coordinates[2] = sf::Vector2i(5, 0);
        coordinates[3] = sf::Vector2i(6, 0);
    }
    else if (type == 3) {
        coordinates[0] = sf::Vector2i(4, 0);
        coordinates[1] = sf::Vector2i(5, 0);
        coordinates[2] = sf::Vector2i(5, 1);
        coordinates[3] = sf::Vector2i(6, 1);
    }
    else if (type == 4) {
        coordinates[0] = sf::Vector2i(4, 0);
        coordinates[1] = sf::Vector2i(4, 1);
        coordinates[2] = sf::Vector2i(5, 1);
        coordinates[3] = sf::Vector2i(6, 1);
    }
    else if (type == 5) {
        coordinates[0] = sf::Vector2i(4, 0);
        coordinates[1] = sf::Vector2i(4, 1);
        coordinates[2] = sf::Vector2i(5, 1);
        coordinates[3] = sf::Vector2i(5, 0);
    }
    else {
        coordinates[0] = sf::Vector2i(4, 1);
        coordinates[1] = sf::Vector2i(5, 1);
        coordinates[2] = sf::Vector2i(5, 0);
        coordinates[3] = sf::Vector2i(6, 1);
    }
    centerLocation = location;
}
void Tetromino::rotate() {
    typeOfRotate = (typeOfRotate + 1) % 4;
}
void Tetromino::speedUp() {
    speed = std::min(speed + 0.05, maxSpeed);
}
void Tetromino::moveLeft() {
    centerLocation.x -= blockSize.x;
    for (int i = 0; i < 4; ++i) coordinates[i].x -= 1;
}
void Tetromino::moveRight() {
    centerLocation.x += blockSize.x;
    for (int i = 0; i < 4; ++i) coordinates[i].x += 1;
}
void Tetromino::moveDown() {
    centerLocation.y += blockSize.y;
    for (int i = 0; i < 4; ++i) coordinates[i].y += 1;
}
void Tetromino::moveUp() {
    centerLocation.y -= blockSize.y;
    for (int i = 0; i < 4; ++i) coordinates[i].y -= 1;
}

sf::Sprite* Tetromino::getSpriteBlocks() {
    if (typeOfTetromino == 0) { // I
        if (typeOfRotate == 0) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - 2*blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y - blockSize.y));
        }
        else if (typeOfRotate == 1) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - 2*blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
        }
        else if (typeOfRotate == 2) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - 2*blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
        }
        else {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - 2*blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y + blockSize.y));
        }
    }
    else if (typeOfTetromino == 1) { // L
        if (typeOfRotate == 0) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y - blockSize.y));
        }
        else if (typeOfRotate == 1) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y + blockSize.y));
        }
        else if (typeOfRotate == 2) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
        }
        else {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
        }
    }
    else if (typeOfTetromino == 2) { // S
        if (typeOfRotate == 0) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y - blockSize.y));
        }
        else if (typeOfRotate == 1) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y + blockSize.y));
        }
        else if (typeOfRotate == 2) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
        }
        else {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
        }
    }
    else if (typeOfTetromino == 3) { // Z
        if (typeOfRotate == 0) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
        }
        else if (typeOfRotate == 1) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y - blockSize.y));
        }
        else if (typeOfRotate == 2) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y + blockSize.y));
        }
        else {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y + blockSize.y));
        }
    }
    else if (typeOfTetromino == 4) { // J
        if (typeOfRotate == 0) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
        }
        else if (typeOfRotate == 1) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
        }
        else if (typeOfRotate == 2) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y - blockSize.y));
        }
        else {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y + blockSize.y));
        }
    }
    else if (typeOfTetromino == 5) { // O
        tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y - blockSize.y));
        tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
        tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
        tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
    }
    else { // T
        if (typeOfRotate == 0) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
        }
        else if (typeOfRotate == 1) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
        }
        else if (typeOfRotate == 2) {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y));
        }
        else {
            tetrominoBlocks[0].setPosition(sf::Vector2f(centerLocation.x - blockSize.x, centerLocation.y));
            tetrominoBlocks[1].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y));
            tetrominoBlocks[2].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y - blockSize.y));
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x, centerLocation.y + blockSize.y));
        }
    }
    return tetrominoBlocks;
}

sf::Vector2i* Tetromino::getCoordinates() {
    return coordinates;
}