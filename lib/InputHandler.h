#pragma once

#include <GLFW/glfw3.h>

class Player;
class Maze;

class InputHandler {
private:
    static bool keys[1024];
    
public:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void processInput(Player& player, Maze& maze, float deltaTime);
};
