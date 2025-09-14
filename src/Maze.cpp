#include "Maze.h"

Maze::Maze() : maze(MAZE_HEIGHT, std::vector<int>(MAZE_WIDTH, WALL)), rng(std::random_device{}()) {}

bool Maze::isValid(int x, int y) {
    return x > 0 && x < MAZE_WIDTH - 1 && y > 0 && y < MAZE_HEIGHT - 1;
}

std::vector<Maze::Cell> Maze::getUnvisitedNeighbors(int x, int y) {
    std::vector<Cell> neighbors;
    if (isValid(x + 2, y) && maze[y][x + 2] == WALL) neighbors.emplace_back(x + 2, y);
    if (isValid(x - 2, y) && maze[y][x - 2] == WALL) neighbors.emplace_back(x - 2, y);
    if (isValid(x, y + 2) && maze[y + 2][x] == WALL) neighbors.emplace_back(x, y + 2);
    if (isValid(x, y - 2) && maze[y - 2][x] == WALL) neighbors.emplace_back(x, y - 2);
    return neighbors;
}

void Maze::carvePath(int x1, int y1, int x2, int y2) {
    maze[y1][x1] = EMPTY;
    maze[y2][x2] = EMPTY;

    maze[(y1 + y2) / 2][(x1 + x2) / 2] = EMPTY;
}

void Maze::generate() {
    std::stack<Cell> cellStack;
    int startX = 1;
    int startY = 1;
    maze[startY][startX] = EMPTY;
    cellStack.push(Cell(startX, startY));

    while (!cellStack.empty()) {
        Cell current = cellStack.top();
        auto neighbors = getUnvisitedNeighbors(current.x, current.y);

        if (!neighbors.empty()) {
            std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
            Cell chosen = neighbors[dist(rng)];
            carvePath(current.x, current.y, chosen.x, chosen.y);
            cellStack.push(chosen);
        } else {
            cellStack.pop();
        }
    }
}

int Maze::getCell(int x, int y) {
    if (isValid(x, y)) {
        return maze[y][x];
    }
    return WALL;
}

const std::vector<std::vector<int>>& Maze::getMaze() const {
    return maze;
}