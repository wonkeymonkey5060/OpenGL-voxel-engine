#version 330 core

layout (location = 0) in vec3 v_Position;  // Vertex position
layout (location = 1) in vec2 aTexCoord;  // Texture Coordinates


out vec2 TexCoord;


uniform mat4 projection;  // Projection matrix
uniform mat4 model;       // Model matrix
uniform mat4 view;        // View matrix


void main() {
    gl_Position = projection * view * model * vec4(v_Position, 1.0);
    TexCoord = aTexCoord;
}
