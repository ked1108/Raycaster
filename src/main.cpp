#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"
#include "Maze.h"
#include "Player.h"
#include "Raycaster.h"
#include "InputHandler.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(gConfig.screenWidth, gConfig.screenHeight, "Raycaster Maze", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, InputHandler::keyCallback);
    
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Initialize backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    


    
    // Set viewport
    glViewport(0, 0, gConfig.screenWidth, gConfig.screenHeight);
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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");
        ImGui::SliderAngle("FOV", &gConfig.fov, 30.0f, 120.0f);
        ImGui::SliderFloat("Move Speed", &gConfig.moveSpeed, 1.0f, 10.0f);
        ImGui::SliderFloat("Turn Speed", &gConfig.turnSpeed, 0.5f, 5.0f);
        ImGui::End();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanup
    glfwTerminate();
    return 0;
}