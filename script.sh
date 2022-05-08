#!/bin/sh
g++ main.cpp objects/button/button.cpp objects/tetromino/tetromino.cpp objects/tetromino/tetrominoGenerator.cpp -o tetris -lsfml-graphics -lsfml-window -lsfml-system 
./tetris