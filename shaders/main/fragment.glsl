#version 330 core

in vec2 TexCoord;
out vec4 FragColor;
in vec4 f_worldPosition;

uniform vec3 cameraPos;
uniform sampler2D textureSampler;

void main() {
    // Hardcoded Fog Parameters
    vec3 fogColor = vec3(0.624, 0.812, 1.0); // light blue fog color
    float fogStart = 30.0f; // Distance at which fog starts
    float fogEnd = 70.0f; // Distance at which fog is fully opaque
    float vFogDepth = length(cameraPos - f_worldPosition.xyz);

    float fogFactor = clamp((fogEnd - vFogDepth) / (fogEnd - fogStart), 0.0, 1.0);

    // Get the texture color
    vec4 texColor = texture(textureSampler, TexCoord);

    // If alpha value is below a threshold, discard the fragment (make it transparent)
    if (texColor.a < 0.1) {
        discard; // Discards the fragment if alpha is low (i.e., transparent)
    }

    // Apply the fog effect by blending the fog color with the texture color
    FragColor = mix(vec4(fogColor, 1.0), texColor, fogFactor);
}

