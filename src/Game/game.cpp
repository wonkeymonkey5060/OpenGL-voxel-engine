#include "game.h"

// Callback function to adjust the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    auto& game = *static_cast<Game*>(glfwGetWindowUserPointer(window));
    game.screenWidth  = width;
    game.screenHeight = height;
    game.updateProjection(width, height);
}


Game::Game() {
    // start glfw window
    if (!glfwInit()) {
        window = nullptr;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1200, 1200, "Hello Window", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Set the framebuffer size callback to adjust the OpenGL viewport when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set the game object associated with the glfw window
    glfwSetWindowUserPointer(window, this);

    // load opengl 3.3 core
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // set up opengl
    glClearColor(0.624f, 0.812f, 1.0f, 1.0f);  // sets the color of the screen
    glEnable(GL_DEPTH_TEST);  // enables depth testing

    shaderProgram = createShader("../shaders/main/vertex.glsl", "../shaders/main/fragment.glsl");
    glUseProgram(shaderProgram);


    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    aspectRatio = static_cast<float>(width) / static_cast<float>(height);


    glm::mat4 projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    GLint projection_location = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));



    player = Player({0.0f, 0.0f, 4.0f}, {-30.0f, -90.0f, 0.0f});


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330"); // or whatever GLSL version you're using

    double chunkstarttime = glfwGetTime();
    chunks.push_back(new Chunk(0, 0));
    chunks.push_back(new Chunk(16, 0));


    material = new Material();
    std::cout << glfwGetTime() - chunkstarttime << std::endl;
    glDisable(GL_CULL_FACE);
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    overlay = new Overlay();

    blockOutline = new BlockOutline();



}

void Game::startLoop() {

    frameskip = 60.0f/clock.fps;

    if (!window) return;
    material->use();
    
    while (!glfwWindowShouldClose(window)) {  // Main Game Loop

        frameskip = 60.0f/clock.fps;

        glClear(GL_COLOR_BUFFER_BIT);  // clears colors from the screen
        glClear(GL_DEPTH_BUFFER_BIT);  // clears all fragments from depth buffer

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "projection"),
            1, GL_FALSE,
            glm::value_ptr(projection)
        );

        
        controls();

        player.update();
        
        material->use();
        for (Chunk* c : chunks) {
            c->draw();
           
        }


        ImGuiIO& io = ImGui::GetIO();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Your dev UI
        ImGui::Begin("Debug Info");
        ImGui::Text("FPS: %i", static_cast<int>(io.Framerate));
        // Add more info here
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        blockOutline->draw();
        overlay->draw(screenWidth, screenHeight);
        
        glfwSwapBuffers(window);

        glfwPollEvents();

        clock.tick();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::controls(){
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player.position[0] += 0.06*frameskip*player.forward2d[0];
        player.position[2] += 0.06*frameskip*player.forward2d[2];
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player.position[0] -= 0.06*frameskip*player.forward2d[0];
        player.position[2] -= 0.06*frameskip*player.forward2d[2];
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.position[0] += 0.06*frameskip*player.right[0];
        player.position[2] += 0.06*frameskip*player.right[2];
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.position[0] -= 0.06*frameskip*player.right[0];
        player.position[2] -= 0.06*frameskip*player.right[2];
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        player.position[1] += 0.06*frameskip;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        player.position[1] -= 0.06*frameskip;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        player.rotation[0] += 1*frameskip;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        player.rotation[0] -= 1*frameskip;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        player.rotation[1] += 1*frameskip;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
       player.rotation[1] -= 1*frameskip;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && (abs(glfwGetTime()-lastBlockBrokenTime)>0.2)) {
        player.rayCast(chunks);
        if (player.blockSelected){ 
            player.targetChunk->removeBlock(player.targetBlock);
            lastBlockBrokenTime = glfwGetTime();
        }

    }
}

void Game::updateProjection(int width, int height) {
    aspectRatio = float(width) / float(height);
    projection  = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

    GLint loc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
}
