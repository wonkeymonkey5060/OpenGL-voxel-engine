#include "player.h"

Camera::Camera(std::array<float, 3> pos, std::array<float, 3> rot){
	this->position=pos;
	this->rotation=rot;
}

void Camera::update(){
	float pitch = glm::radians(rotation[0]);
    float yaw   = glm::radians(rotation[1]);

    
    forward.x = cos(pitch) * cos(yaw);
    forward.y = sin(pitch);
    forward.z = cos(pitch) * sin(yaw);
    forward = glm::normalize(forward);

    forward2d.x = cos(yaw);
    forward2d.y = 0.0;
    forward2d.z = sin(yaw);
    forward2d = glm::normalize(forward2d);

    yaw   = glm::radians(rotation[1]-90);
    right.x = cos(yaw);
    right.y = 0.0;
    right.z = sin(yaw);
    right = glm::normalize(right);

    glm::vec3 eye    = glm::vec3(position[0], position[1], position[2]);
    glm::vec3 target = eye + forward;
    glm::vec3 up     = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view = glm::lookAt(eye, target, up);

	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

	GLuint viewLoc = glGetUniformLocation(currentProgram, "view");
    GLuint camLoc = glGetUniformLocation(currentProgram, "cameraPos");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(camLoc, 1, glm::value_ptr(eye));
}	


Player::Player(std::array<float, 3> pos, std::array<float, 3> rot){
    this->position=pos;
    this->rotation=rot;
    camera = new Camera(pos, rot);

    forward = camera->forward;
    forward2d = camera->forward2d;
    right = camera->right;
}

void Player::update(){
    camera->position = position;
    camera->rotation = rotation;
    camera->update();

    forward = camera->forward;
    forward2d = camera->forward2d;
    right = camera->right;
}
void Player::rayCast(std::vector<Chunk*> world){
    std::vector<Chunk*> nearChunks;
    for (Chunk* chunk : world){
        if ( (abs(chunk->position[0]-position[0]) <= 16) && (abs(chunk->position[1]-position[2]) <= 16)){
            nearChunks.emplace_back(chunk);
            
        }
    }


    blockSelected = false;
    std::array<float, 3> step = {position[0], position[1], position[2]};
    std::array<int, 3> roundedStep = {static_cast<int>(std::round(step[0])), static_cast<int>(std::round(step[1])), static_cast<int>(std::round(step[2]))};
    int rayHit = 0;
    for (int i = 0; i < 640; i++){
        step[0] += forward[0]/100;
        step[1] += forward[1]/100;
        step[2] += forward[2]/100;
        roundedStep = {static_cast<int>(std::round(step[0])), static_cast<int>(std::round(step[1])), static_cast<int>(std::round(step[2]))};
        for (Chunk* chunk : nearChunks){
            if (chunk->unorderedWorldBlocks.find(roundedStep) != chunk->unorderedWorldBlocks.end()) {
                blockSelected = true;
                targetBlock={roundedStep[0]-chunk->position[0], roundedStep[1], roundedStep[2]-chunk->position[1]};
                targetChunk=chunk;
                return;
            }
        }
    }
    
}