#include "main.h" 
        

#include <direct.h> // For Windows

void printWorkingDirectory() {
    char buffer[FILENAME_MAX];
    _getcwd(buffer, sizeof(buffer)); // For Windows
    std::cout << "Current working directory: " << buffer << std::endl;
}

int main() {
    printWorkingDirectory();

    Game game;

    game.startLoop();

    return 0;
}
