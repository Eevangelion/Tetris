#pragma once
#include "tetromino.h"
#include <chrono>
#include <random>

class TetrominoGenerator {
    int bag[7];
    int currentType;
    sf::Vector2f centerLocation;
    sf::Vector2f blockSize;
    std::mt19937 rnd;
    std::uniform_int_distribution<int> uid;
public:
    TetrominoGenerator(sf::Vector2f, sf::Vector2f);
    Tetromino* nextTetromino();
    ~TetrominoGenerator();
};