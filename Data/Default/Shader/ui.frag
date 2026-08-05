#version 450

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

void main() {
    // UI keeps alpha for smooth edges and font-like content.
    outColor = fragColor * texture(texSampler, fragTexCoord);
}
