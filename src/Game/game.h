#ifndef GAME_H
#define GAME_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // Required before glad.h on Windows
#include <glad/glad.h>    
#include <GLFW/glfw3.h>   
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <iostream>
#include <memory>
#include <vector>
#include <random>


#include "../Clock/clock.h"
#include "../Graphics/graphics.h"
#include "../Entities/entities.h"
#include "../World/world.h"
#include "../Player/player.h"
#include "../Blocktypes/blocktypes.h"

class Game {
public:
    Game();            // Constructor
    void startLoop();  // Starts the game loop
    void updateProjection(int width, int height);
    void controls();
    int screenWidth, screenHeight;


private:
    GLFWwindow* window;
    Clock clock;
    GLuint shaderProgram;
    

    float fov = glm::radians(60.0f);
    float aspectRatio = 800.0f / 600.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    glm::mat4 projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    


    Camera camera;

    Drone* drone;
    
    Block* woodblock;
    Material* material = nullptr;
    Chunk* chunk = nullptr;
    Chunk* chunk2 = nullptr;
    std::vector<Chunk*> chunks;
    float frameskip;
    double lastBlockBrokenTime = glfwGetTime();
    Player player;
    Overlay* overlay;
    BlockOutline* blockOutline = nullptr;


};


#endif // GAME_H

