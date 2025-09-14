#pragma once

#include <cmath>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int MAZE_WIDTH = 21;
const int MAZE_HEIGHT = 21;

const float FOV = M_PI / 3.0f; // 60 degrees
const float WALL_HEIGHT = 1.0f;

const float MOVE_SPEED = 3.0f; // units per second
const float TURN_SPEED = 1.0f; // radians per second

enum CellType {
    WALL  = 0,
    EMPTY = 1,
};