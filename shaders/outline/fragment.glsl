#version 330 core


in vec2 TexCoord;
out vec4 FragColor;


uniform sampler2D textureSampler;

void main() {
    //FragColor = texture(textureSampler, TexCoord);
    FragColor = vec4(1.0f, 0.0f, 0.0f, 0.5f);

}
