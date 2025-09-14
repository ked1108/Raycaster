#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Constants.h"
#include "Maze.h"
#include "Player.h"
#include "Raycaster.h"
#include "InputHandler.h"

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster Maze", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, InputHandler::keyCallback);
    
    // Initialize GLEW
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // Set viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Generate maze
    Maze maze;
    maze.generate();
    
    // Create player at starting position
    Player player(1.5f, 1.5f, 0.0f);
    
    // Create raycaster
    Raycaster raycaster;
    
    std::cout << "Controls:" << std::endl;
    std::cout << "WASD - Move" << std::endl;
    std::cout << "Arrow Keys - Turn" << std::endl;
    std::cout << "ESC - Exit" << std::endl;
    
    // Timing variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Process input
        InputHandler::processInput(player, maze, deltaTime);
        
        // Render
        raycaster.render(player, maze);
        
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanup
    glfwTerminate();
    return 0;
}