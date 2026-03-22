#include "clock.h"

Clock::Clock()
{
    currentTick = glfwGetTime();
    lastTick = glfwGetTime();
    fps = currentTick-lastTick;
    if (fps <= 0){
        fps = 1;
    }
}

void Clock::tick() {
    lastTick = currentTick;
    currentTick = glfwGetTime();
    fps = 1/(currentTick-lastTick);
    if (fps <= 0){
        fps = 1;
    }
}

