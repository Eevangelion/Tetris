#include "tetrominoGenerator.h"

TetrominoGenerator::TetrominoGenerator(sf::Vector2f location, sf::Vector2f sizeOfBlock) {
        std::random_shuffle(bag, bag + 7);
        centerLocation = location;
        blockSize = sizeOfBlock;
        currentType = 0;
    }
Tetromino* TetrominoGenerator::nextTetromino() {
    if (currentType == 7) {
        currentType = 0;
        std::random_shuffle(bag, bag + 7);
    }
    return new Tetromino(centerLocation, blockSize, bag[currentType++]);
}