#pragma once

#include "Vec2.h"
#include "Config.h"

class Maze; //Forward Declaration

class Player {
    public:
    Vec2 pos;
    float angle;
    Vec2 dir;

    Player (float x, float y, float a);

    void updateDirection();
    void move(float distance, Maze& maze);
    void strafe(float distance, Maze& maze);
    void rotate(float deltaAngle);
};

