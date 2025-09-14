#include "InputHandler.h"
#include "Player.h"
#include "Maze.h"
#include "Constants.h"

bool InputHandler::keys[1024] = {false};

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void InputHandler::processInput(Player& player, Maze& maze, float deltaTime) {
    float moveSpeed = MOVE_SPEED * deltaTime;
    float turnSpeed = TURN_SPEED * deltaTime;
    
    // Movement
    if (keys[GLFW_KEY_W]) {
        player.move(moveSpeed, maze);
    }
    if (keys[GLFW_KEY_S]) {
        player.move(-moveSpeed, maze);
    }
    if (keys[GLFW_KEY_A]) {
        player.strafe(-moveSpeed, maze);
    }
    if (keys[GLFW_KEY_D]) {
        player.strafe(moveSpeed, maze);
    }
    
    // Rotation
    if (keys[GLFW_KEY_LEFT]) {
        player.rotate(-turnSpeed);
    }
    if (keys[GLFW_KEY_RIGHT]) {
        player.rotate(turnSpeed);
    }
}