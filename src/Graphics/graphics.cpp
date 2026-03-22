#include "graphics.h"


Mesh::Mesh(std::string model_path) {

    std::vector<float> data = loadObj("../models/" + model_path);
    
    if (data.empty()) {
        std::cerr << "Failed to load OBJ\n";
        return;
    }

    num_vertices = data.size() / 8;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW
    );


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //    – 3 floats, offset 0, stride = 8 * sizeof(float)
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);
}


void Mesh::prepare() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}




Part::Part(const Mesh& mesh) : mesh(mesh){ 
}

void Part::draw(){
    mesh.prepare();
    
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    GLint model_location = glGetUniformLocation(currentProgram, "model");

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position[0], position[1], position[2]));

    model = glm::rotate(model, glm::radians(rotation[0]), {1,0,0});
    model = glm::rotate(model, glm::radians(rotation[1]), {0,1,0});
    model = glm::rotate(model, glm::radians(rotation[2]), {0,0,1});

    model = glm::scale(model, scale);

    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, mesh.num_vertices);
}









Material::Material(const std::string& path, bool clamp) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(("../gfx/" + path).c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture at path: " << path
                  << " (reason: " << stbi_failure_reason() << ")\n";
        return;
    }

    glGenTextures(1, &textureID); // textureID member is declared in graphics.h
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping mode
    if (clamp) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Horizontal wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Vertical wrapping
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Horizontal wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Vertical wrapping
    }

    // Set texture filtering (you can keep this if you want)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}


void Material::use(){
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    glActiveTexture(GL_TEXTURE0); // activates texture unit 0
    glBindTexture(GL_TEXTURE_2D, textureID); // binds the texture to texture unit 0
    GLint texLoc = glGetUniformLocation(currentProgram, "textureSampler");
    glUniform1i(texLoc, 0); // sets the textureSampler sampler2D object to use texture unit 0
}



GLuint createShader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Read shader code from files
    std::ifstream vFile(vertexPath);
    std::ifstream fFile(fragmentPath);
    std::stringstream vStream, fStream;

    if (!vFile.is_open() || !fFile.is_open()) {
        std::cerr << "Failed to open shader files.\n";
        return 0;
    }

    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();
    std::string vertexCode = vStream.str();
    std::string fragmentCode = fStream.str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    // Check for compile errors
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return 0;
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);

    // Check for compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        return 0;
    }

    // Link shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
        return 0;
    }

    // Clean up shaders (no longer needed after linking)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

Overlay::Overlay()
    : crosshair(Mesh("crosshair.obj"))
{
    shaderProgram = createShader("../shaders/overlay/vertex.glsl", "../shaders/overlay/fragment.glsl");
    material = new Material("crosshair.png", true);
}

void Overlay::draw(int screenWidth, int screenHeight) {
    material->use();
    glUseProgram(shaderProgram);
    glDisable(GL_DEPTH_TEST);

    // 1) set up 2D camera
    glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth,
                                0.0f, (float)screenHeight);
    glm::mat4 view = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"),
                       1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"),
                       1, GL_FALSE, glm::value_ptr(view));

    // 2) build a single model matrix with BOTH translate and scale
    float cx = screenWidth  * 0.5f;
    float cy = screenHeight * 0.5f;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {cx, cy, 0.0f});
    model = glm::scale(    model, {3.0f, 3.0f, 1.0f});  // ← change 10.0 to whatever size you want

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(model));

    // 3) draw the crosshair mesh directly
    crosshair.mesh.prepare();
    glDrawArrays(GL_TRIANGLES, 0, crosshair.mesh.num_vertices);

    glEnable(GL_DEPTH_TEST);
}

BlockOutline::BlockOutline(){
    part = new Part(Mesh("cube.obj"));
    part->scale = {1.001, 1.001, 1.001};
    material = new Material("blockoutline.png", true);
}

void BlockOutline::draw(){
    part->position[0] = (float)position[0];
    part->position[1] = (float)position[1];
    part->position[2] = (float)position[2];

    
    material->use();
    part->draw();
}

