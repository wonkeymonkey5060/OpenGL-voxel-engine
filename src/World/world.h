#ifndef WORLD_H
#define WORLD_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // Required before glad.h on Windows
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>      // for std::string
#include <iostream>    // for std::cerr, std::cout, etc.
#include <vector>
#include <unordered_set>
#include <array>

using namespace std;
namespace std {
    template <>
    struct hash<std::array<int, 3>> {
        std::size_t operator()(const std::array<int, 3>& arr) const {
            return arr.at(0) ^ (arr.at(1) << 1) ^ (arr.at(2) << 2);
        }
    };
}



#include "../Entities/entities.h"
#include "../Graphics/graphics.h"



class Block {
public:
    std::array<int, 3> position = {0, 0, -6};
    std::array<float, 3> rotation = {0.0f, 0.0f, 0.0f};

    std::array<float, 2> texOffset = {0.0f, 0.0f};
    std::array<float, 2> texSize = {512.0f, 512.0f};
    std::array<float, 2> uvStart;
    std::array<float, 2> uvSize;

    std::vector<float> vertices;
    static constexpr float texMapSize = 512.0f;
    float pixel = 1.0f/texMapSize;


    int verticesIndex = 0;

    Block(int x, int y, int z) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        uvStart = {texOffset[0]/texMapSize, texOffset[1]/texMapSize};
        uvSize = {texSize[0]/texMapSize, texSize[1]/texMapSize};

    }
    void setVertexArray(std::array<bool, 6> faces);
    void addToChunkMesh(std::vector<float>* chunk_vertices);
    void removeFromChunkMesh(std::vector<float>* chunk_vertices);
    virtual ~Block() = default; // Always a good idea for base classes
};





class Chunk {
public:
    std::array<int, 2> position = {0, 0};
    std::vector<float> vertices = {};
    std::vector<Block> blocks = {};

    int num_vertices;

    std::unordered_set<std::array<int, 3>> unorderedBlocks;
    std::unordered_set<std::array<int, 3>> unorderedWorldBlocks;


    GLuint vao;  
    GLuint vbo; 

    

    Chunk(int x = 0, int z = 0);

    glm::mat4 model;
    GLint currentProgram;
    GLint modelLoc;

    void initMesh();
    void setMeshVertices();
    void addBlock(array<int, 3> pos){
        blocks.emplace_back(pos[0], pos[1], pos[2]);
        unorderedBlocks.insert({pos[0], pos[1], pos[2]});
        unorderedWorldBlocks.insert({pos[0]+position[0], pos[1], pos[2]+position[1]});
    }
    void draw();
    bool isBlockAt(const std::array<int, 3>& pos){
        if (unorderedBlocks.find(pos) != unorderedBlocks.end()) {
            return true;}
        return false;}
    void setAdjacentChunk(std::unordered_set<std::array<int, 3>> adjacentBlocks);
    void removeBlock(array<int, 3> pos);

};

#endif // WORLD_H

