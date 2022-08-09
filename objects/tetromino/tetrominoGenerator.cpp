#include "tetrominoGenerator.h"

TetrominoGenerator::TetrominoGenerator(sf::Vector2f location, sf::Vector2f sizeOfBlock) {
    for (int i = 0; i < 7; ++i) bag[i] = i;
    rnd.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::shuffle(bag, bag + 7, rnd);
    centerLocation = location;
    blockSize = sizeOfBlock;
    currentType = 0;
}
Tetromino* TetrominoGenerator::nextTetromino() {
    if (currentType == 7) {
        currentType = 0;
        std::shuffle(bag, bag + 7, rnd);
    }
    return new Tetromino(centerLocation, blockSize, bag[currentType++]);
}