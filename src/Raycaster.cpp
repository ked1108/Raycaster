#include "Raycaster.h"
#include "Player.h"
#include "Maze.h"

#include <cmath>
#include <algorithm>

Raycaster::RayHit Raycaster::castRay(const Vec2& origin, float angle, Maze& maze) {
    Vec2 rayDir(cos(angle), sin(angle));
    
    // DDA Algorithm for raycasting
    int mapX = (int)origin.x;
    int mapY = (int)origin.y;
    
    float deltaDistX = fabs(1.0f / rayDir.x);
    float deltaDistY = fabs(1.0f / rayDir.y);
    
    float perpWallDist;
    int stepX, stepY;
    float sideDistX, sideDistY;
    
    if (rayDir.x < 0) {
        stepX = -1;
        sideDistX = (origin.x - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0f - origin.x) * deltaDistX;
    }
    
    if (rayDir.y < 0) {
        stepY = -1;
        sideDistY = (origin.y - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0f - origin.y) * deltaDistY;
    }
    
    bool hit = false;
    bool side; // Was it a NS or a EW wall hit?
    
    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = false;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = true;
        }
        
        if (maze.getCell(mapX, mapY) == WALL) {
            hit = true;
        }
    }
    
    if (!side) {
        perpWallDist = (mapX - origin.x + (1 - stepX) / 2) / rayDir.x;
    } else {
        perpWallDist = (mapY - origin.y + (1 - stepY) / 2) / rayDir.y;
    }
    
    RayHit result;
    result.distance = perpWallDist;
    result.hitWall = true;
    result.isVerticalWall = !side;
    
    // Calculate wall X coordinate for texturing
    if (!side) {
        result.wallX = origin.y + perpWallDist * rayDir.y;
    } else {
        result.wallX = origin.x + perpWallDist * rayDir.x;
    }
    result.wallX -= floor(result.wallX);
    
    return result;
}

void Raycaster::render(const Player& player, Maze& maze) {
    wallDistances.clear();
    wallDistances.resize(SCREEN_WIDTH);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render ceiling (dark gray)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    
    // Render floor (dark brown)
    glColor3f(0.2f, 0.1f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
    
    // Cast rays for each screen column
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calculate ray angle
        float cameraX = 2.0f * x / (float)SCREEN_WIDTH - 1.0f;
        float rayAngle = player.angle + atan(cameraX * tan(FOV / 2));
        
        RayHit hit = castRay(player.pos, rayAngle, maze);
        wallDistances[x] = hit.distance;
        
        // Calculate wall height
        float wallHeight = WALL_HEIGHT / hit.distance;
        wallHeight = std::min(wallHeight, 2.0f); // Cap wall height
        
        // Calculate wall color based on distance and orientation
        float brightness = 1.0f / (1.0f + hit.distance * hit.distance * 0.1f);
        brightness = std::max(brightness, 0.1f);
        
        if (hit.isVerticalWall) {
            glColor3f(brightness * 0.8f, brightness * 0.6f, brightness * 0.4f);
        } else {
            glColor3f(brightness * 0.6f, brightness * 0.4f, brightness * 0.2f);
        }
        
        // Draw wall column
        float screenX = -1.0f + 2.0f * x / SCREEN_WIDTH;
        float wallTop = wallHeight;
        float wallBottom = -wallHeight;
        
        glBegin(GL_LINES);
        glVertex2f(screenX, wallBottom);
        glVertex2f(screenX, wallTop);
        glEnd();
    }
    
    // Render minimap
    renderMinimap(player, maze);
}

void Raycaster::renderMinimap(const Player& player, Maze& maze) {
    float minimapSize = 0.3f;
    float minimapScale = minimapSize / std::max(MAZE_WIDTH, MAZE_HEIGHT);
    
    // Position minimap in top-right corner
    float minimapX = 0.7f;
    float minimapY = 0.7f;
    
    // Draw maze
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            float cellX = minimapX + x * minimapScale;
            float cellY = minimapY + y * minimapScale;
            
            if (maze.getCell(x, y) == WALL) {
                glColor3f(0.8f, 0.8f, 0.8f); // White for walls
            } else {
                glColor3f(0.2f, 0.2f, 0.2f); // Dark for empty space
            }
            
            glBegin(GL_QUADS);
            glVertex2f(cellX, cellY);
            glVertex2f(cellX + minimapScale, cellY);
            glVertex2f(cellX + minimapScale, cellY + minimapScale);
            glVertex2f(cellX, cellY + minimapScale);
            glEnd();
        }
    }
    
    // Draw player
    float playerX = minimapX + player.pos.x * minimapScale;
    float playerY = minimapY + player.pos.y * minimapScale;
    
    glColor3f(1.0f, 0.0f, 0.0f); // Red for player
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(playerX, playerY);
    glEnd();
    
    // Draw player direction
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow for direction
    glBegin(GL_LINES);
    glVertex2f(playerX, playerY);
    glVertex2f(playerX + player.dir.x * minimapScale * 3,
              playerY + player.dir.y * minimapScale * 3);
    glEnd();
}