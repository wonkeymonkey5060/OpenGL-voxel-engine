#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // Required before glad.h on Windows
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION



// Game source files
#include "Game/game.h"




#endif // PCH_H