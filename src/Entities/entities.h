// entities.h
#ifndef ENTITIES_H
#define ENTITIES_H

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../Graphics/graphics.h"


class Entity {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~Entity() = default;
    std::array<float, 3> position = {0.0f, 0.0f, 0.0f};
    std::array<float, 3> rotation = {0.0f, 0.0f, 0.0f};
};


class Drone : public Entity {
public:
    Drone(std::array<float, 3> pos = {0.0f, 0.0f, 0.0f}, std::array<float, 3> rot = {0.0f, 0.0f, 0.0f}, std::string materialpath="stone.jfif");  // Constructor that expects a Mesh object
    void draw() override;
    void update() override;
    std::vector<Part*> parts = { new Part(Mesh("drone.obj")) };
    Material material;

};

#endif
