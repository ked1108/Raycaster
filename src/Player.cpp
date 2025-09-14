#include "Vec2.h"
#include "Player.h"
#include "Maze.h"
#include "Constants.h"

Player::Player(float x, float y, float a) : pos(x, y), angle(a) {
    updateDirection();
}

void Player::updateDirection() {
    dir.x = cos(angle);
    dir.y = sin(angle);
}

void Player::move(float distance, Maze& maze) {
    Vec2 newPos = pos + dir * distance;

    int mapX = (int) newPos.x;
    int mapY = (int) newPos.y;

    if (maze.getCell(mapX, mapY) == EMPTY) {
        pos = newPos;
    }
}

void Player::strafe(float distance, Maze& maze) {
    Vec2 strafeDir(-dir.y, dir.x);
    Vec2 newPos = pos + strafeDir * distance;

    
    int mapX = (int) newPos.x;
    int mapY = (int) newPos.y;

    if (maze.getCell(mapX, mapY) == EMPTY) {
        pos = newPos;
    }
}

void Player::rotate(float deltaAngle) {
    angle += deltaAngle;
    if (angle < 0) angle += 2 * M_PI;
    if (angle >= 2 * M_PI) angle -= 2 * M_PI;
    updateDirection();
}