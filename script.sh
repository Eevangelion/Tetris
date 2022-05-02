#!/bin/sh
g++ -c main.cpp
g++ main.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system
./tetris