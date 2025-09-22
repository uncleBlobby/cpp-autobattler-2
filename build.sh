#!/bin/bash

g++ ./src/main.cpp ./src/game.cpp ./src/player.cpp ./src/enemy.cpp ./src/projectile.cpp -o ./build/main -std=c++20 -I/usr/local/include -L/usr/local/lib64 -lraylib -Wall -Wextra