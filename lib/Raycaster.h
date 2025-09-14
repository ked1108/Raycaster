#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vec2.h"
#include "Constants.h"

class Player;
class Maze;

class Raycaster {
private:
    std::vector<float> wallDistances;
    
    struct RayHit {
        float distance;
        bool hitWall;
        float wallX;
        bool isVerticalWall;
    };
    
    RayHit castRay(const Vec2& origin, float angle, Maze& maze);
    void renderMinimap(const Player& player, Maze& maze);
    
public:
    void render(const Player& player, Maze& maze);
};
