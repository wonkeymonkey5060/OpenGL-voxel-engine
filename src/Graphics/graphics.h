#ifndef GRAPHICS_H
#define GRAPHICS_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // Required before glad.h on Windows
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>      // for std::string
#include <fstream>     // for std::ifstream
#include <sstream>     // for std::stringstream
#include <iostream>    // for std::cerr, std::cout, etc.
#include <vector>

#include "../Objloader/objloader.h"


#include "stb_image.h"



class Mesh {
public:
    GLuint vao;  
    GLuint vbo;        
    int num_vertices;

    Mesh(std::string model_path = "block.obj");
    void prepare();
};

class Material {
public:
    Material(const std::string& path = "grass_block.png", bool clamp = false);
    GLuint textureID; // make sure this is declared here!

    void use();
};

class Part {
public:
    Mesh mesh;
    Part(const Mesh& mesh);
    void draw();
    std::array<float, 3> position = {0.0f, 0.0f, 0.0f};
    std::array<float, 3> rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale = {1, 1, 1};
};

class Overlay {
private:
    Part crosshair;
    GLuint shaderProgram;
    Material* material;

public:
    Overlay();
    void draw(int screenWidth, int screenHeight);
};

class BlockOutline {
private:
    Part* part = nullptr;
    Material* material;
public:
    BlockOutline();
    std::array<int, 3> position = {0,-1,0};
    void draw();
};







GLuint createShader(const std::string& vertexPath, const std::string& fragmentPath);

#endif // GRAPHICS_H
