#ifndef CLOCK_H
#define CLOCK_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // Required before glad.h on Windows

#include <glad/glad.h>    // Include GLAD first
#include <GLFW/glfw3.h>   // Then include GLFW (after glad)

#include <iostream>

class Clock 
{
public:
    float currentTick;
    float lastTick;
    float fps;
    Clock();
    void tick();
    
};

#endif // CLOCK_H