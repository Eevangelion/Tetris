#include "tetromino.h"

class TetrominoGenerator {
    int bag[7] = {0, 1, 2, 3, 4, 5, 6};
    int currentType;
    sf::Vector2f centerLocation;
    sf::Vector2f blockSize;
public:
    TetrominoGenerator(sf::Vector2f, sf::Vector2f);
    Tetromino* nextTetromino();
};