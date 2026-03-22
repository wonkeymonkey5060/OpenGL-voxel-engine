// entities.h
#ifndef BLOCKTYPES_H
#define BLOCKTYPES_H

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../Graphics/graphics.h"
#include "../World/world.h"


// Derived class
class GrassBlock : public Block {
public:
   GrassBlock(int x, int y, int z);
};

#endif //BLOCKTYPES_H