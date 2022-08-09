#include "tetromino.h"
#include <../../SFML/Graphics.hpp>

Tetromino::Tetromino(sf::Vector2f location, sf::Vector2f sizeOfBlock, short type) {
    typeOfTetromino = type;
    speed = 3.5;
    typeOfRotate = 0;
    blockSize = sizeOfBlock;
    textureBlock.loadFromFile("models/block/block.png");
    tetrominoBlocks = new sf::Sprite[4];
    coordinates = new sf::Vector2i[4];
    for (int i = 0; i < 4; ++i) {
        tetrominoBlocks[i].setTexture(textureBlock);
        tetrominoBlocks[i].setScale(sf::Vector2f(blockSize.x / tetrominoBlocks[i].getLocalBounds().width, blockSize.y / tetrominoBlocks[i].getLocalBounds().height));
    }
    if (type == 0) { // I
        coordinates[0] = sf::Vector2i(3, 0);
        coordinates[1] = sf::Vector2i(4, 0);
        coordinates[2] = sf::Vector2i(5, 0);
        coordinates[3] = sf::Vector2i(6, 0);
    }
    else if (type == 1) { // L
        coordinates[0] = sf::Vector2i(4, 1);
        coordinates[1] = sf::Vector2i(5, 1);
        coordinates[2] = sf::Vector2i(6, 1);
        coordinates[3] = sf::Vector2i(6, 0);
    }
    else if (type == 2) { // S
        coordinates[0] = sf::Vector2i(4, 1);
        coordinates[1] = sf::Vector2i(5, 1);
        coordinates[2] = sf::Vector2i(5, 0);
        coordinates[3] = sf::Vector2i(6, 0);
    }
    else if (type == 3) { // Z
        coordinates[0] = sf::Vector2i(4, 0);
        coordinates[1] = sf::Vector2i(5, 0);
        coordinates[2] = sf::Vector2i(5, 1);
        coordinates[3] = sf::Vector2i(6, 1);
    }
    else if (type == 4) { // J
        coordinates[0] = sf::Vector2i(4, 0);
        coordinates[1] = sf::Vector2i(4, 1);
        coordinates[2] = sf::Vector2i(5, 1);
        coordinates[3] = sf::Vector2i(6, 1);
    }
    else if (type == 5) { // O
        coordinates[0] = sf::Vector2i(4, 0);
        coordinates[1] = sf::Vector2i(4, 1);
        coordinates[2] = sf::Vector2i(5, 1);
        coordinates[3] = sf::Vector2i(5, 0);
    }
    else { // T
        coordinates[0] = sf::Vector2i(4, 1);
        coordinates[1] = sf::Vector2i(5, 1);
        coordinates[2] = sf::Vector2i(5, 0);
        coordinates[3] = sf::Vector2i(6, 1);
    }
    centerLocation = location;
    centerCoordinates = sf::Vector2i(5, 1);
}
void Tetromino::rotate() {
    typeOfRotate = (typeOfRotate + 1) % 4;
    if (typeOfTetromino == 0) { // I
        if (typeOfRotate == 0) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 2, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 1);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y - 1);
        }
        else if (typeOfRotate == 1) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 2);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
        }
        else if (typeOfRotate == 2) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 2, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
        }
        else {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 2);
            coordinates[1] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 1);
            coordinates[2] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y + 1);
        }
    }
    else if (typeOfTetromino == 1) { // L
        if (typeOfRotate == 0) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y - 1);
        }
        else if (typeOfRotate == 1) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y + 1);
        }
        else if (typeOfRotate == 2) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y + 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
        }
        else {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
        }
    }
    else if (typeOfTetromino == 2) { // S
        if (typeOfRotate == 0) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y - 1);
        }
        else if (typeOfRotate == 1) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y + 1);
        }
        else if (typeOfRotate == 2) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y + 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
        }
        else {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
        }
    }
    else if (typeOfTetromino == 3) { // Z
        if (typeOfRotate == 0) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
        }
        else if (typeOfRotate == 1) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y - 1);
        }
        else if (typeOfRotate == 2) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y + 1);
        }
        else {
            coordinates[0] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y + 1);
        }
    }
    else if (typeOfTetromino == 4) { // J
        if (typeOfRotate == 0) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
        }
        else if (typeOfRotate == 1) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
        }
        else if (typeOfRotate == 2) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y + 1);
        }
        else {
            coordinates[0] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y + 1);
        }
    }
    else if (typeOfTetromino == 5) { // O
        coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y - 1);
        coordinates[1] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
        coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
        coordinates[3] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
    }
    else { // T
        if (typeOfRotate == 0) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
        }
        else if (typeOfRotate == 1) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
            coordinates[3] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
        }
        else if (typeOfRotate == 2) {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x + 1, centerCoordinates.y);
        }
        else {
            coordinates[0] = sf::Vector2i(centerCoordinates.x - 1, centerCoordinates.y);
            coordinates[1] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y);
            coordinates[2] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y - 1);
            coordinates[3] = sf::Vector2i(centerCoordinates.x, centerCoordinates.y + 1);
        }
    }
}
void Tetromino::speedUp() {
    speed = std::min(speed + 1., maxSpeed);
}
void Tetromino::moveLeft() {
    centerLocation.x -= blockSize.x;
    centerCoordinates.x -= 1;
    for (int i = 0; i < 4; ++i) coordinates[i].x -= 1;
}
void Tetromino::moveRight() {
    centerLocation.x += blockSize.x;
    centerCoordinates.x += 1;
    for (int i = 0; i < 4; ++i) coordinates[i].x += 1;
}
void Tetromino::moveDown() {
    centerLocation.y += blockSize.y;
    centerCoordinates.y += 1;
    for (int i = 0; i < 4; ++i) coordinates[i].y += 1;
}
void Tetromino::moveUp() {
    centerLocation.y -= blockSize.y;
    centerCoordinates.y -= 1;
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
            tetrominoBlocks[3].setPosition(sf::Vector2f(centerLocation.x + blockSize.x, centerLocation.y + blockSize.y));
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

double Tetromino::getSpeed() {
    return speed;
}
void Tetromino::normalSpeed() {
    speed = 3.5;
}

Tetromino::~Tetromino() {
    delete tetrominoBlocks;
    delete coordinates;
}