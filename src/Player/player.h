#ifndef PLAYER_H
#define PLAYER_H

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <glad/glad.h>
#include <cmath>

#include "../World/world.h"

class Camera{
public:
	Camera(std::array<float, 3> pos = {0.0, 0.0, 0.0}, std::array<float, 3> rot = {0.0, 0.0, 0.0});
	void update();
	std::array<float, 3> position = {0.0, 0.0, 0.0};
	std::array<float, 3> rotation = {0.0, 0.0, 0.0};

	glm::vec3 forward = {0.0, 0.0, 1.0};
	glm::vec3 forward2d = {0.0, 0.0, 1.0};

	glm::vec3 right = {1.0, 0.0, 0.0};



	std::array<float, 3> target = {0.0, 0.0, 1.0};
};

class Player{
public:
	std::array<float, 3> position = {0.0, 0.0, 0.0};
	std::array<float, 3> rotation = {0.0, 0.0, 0.0};

	glm::vec3 forward = {0.0, 0.0, 1.0};
	glm::vec3 forward2d = {0.0, 0.0, 1.0};

	glm::vec3 right = {1.0, 0.0, 0.0};

	Camera* camera = nullptr;

	std::vector<Chunk*> chunks;

	std::array<int,3> targetBlock = {0,0,0};
	Chunk* targetChunk = nullptr;
	bool blockSelected = false;


	Player(std::array<float, 3> pos = {0.0, 0.0, 0.0}, std::array<float, 3> rot = {0.0, 0.0, 0.0});
	void update();
	void rayCast(std::vector<Chunk*> world);

};


#endif // PLAYER_H