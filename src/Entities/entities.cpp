// entities.cpp
#include "entities.h"






Drone::Drone(std::array<float, 3> pos, std::array<float, 3> rot, std::string materialpath) : material("..\\gfx\\" + materialpath) {
	this->position = pos;
	this->rotation = rot;
}
void Drone::draw() {
	material.use();
	for (Part* p : parts){
		p->draw();
	}
}
void Drone::update() {
	//for (Part* p : parts){
		/*p->rotation = rotation;
		p->position = position;*/
	//}
}