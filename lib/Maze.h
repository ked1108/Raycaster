#pragma once

#include <vector>
#include <random>
#include <stack>
#include "Constants.h"

class Maze {
private:
    std::vector<std::vector<int>> maze;
    std::mt19937 rng;

    struct Cell {
        int x, y;
        Cell(int x, int y) : x(x), y(y) {}
    };

    
    bool isValid(int x, int y);
    std::vector<Cell> getUnvisitedNeighbors(int x, int y);
    void carvePath(int x1, int y1, int x2, int y2);

public:
    Maze();
    void generate();
    int getCell(int x, int y);
    const std::vector<std::vector<int>>& getMaze() const;

};