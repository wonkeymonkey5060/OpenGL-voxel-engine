#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textureSampler;

void main() {
    vec4 tex = texture(textureSampler, TexCoord);
    if (tex.a < 0.1) discard;
    FragColor = tex;
}
