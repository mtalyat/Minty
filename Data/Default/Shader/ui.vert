#version 450

layout(location = 0) in vec2 quadPosition;
layout(location = 1) in vec2 quadTexCoord;

layout(location = 2) in mat4 instanceTransform;
layout(location = 6) in vec4 instanceColor;
layout(location = 7) in vec2 instanceOffset;
layout(location = 8) in vec2 instanceSize;
layout(location = 9) in vec2 instancePivot;
layout(location = 10) in float instanceScale;
layout(location = 11) in uint instanceFlags;
layout(location = 12) in vec2 instanceTextureSize;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    // Build the element quad from its pixel-space sprite region.
    vec2 local = (quadPosition * instanceSize - instancePivot) * instanceScale;

    // UI is authored in canvas-space and directly transformed into clip-space.
    gl_Position = instanceTransform * vec4(local.x, local.y * -1.0, 0.0, 1.0);

    vec2 texCoord = quadTexCoord;
    if ((instanceFlags & 0x1u) != 0u) {
        texCoord.x = 1.0 - texCoord.x;
    }
    if ((instanceFlags & 0x2u) != 0u) {
        texCoord.y = 1.0 - texCoord.y;
    }

    vec2 textureSize = max(instanceTextureSize, vec2(1.0));
    fragTexCoord = (texCoord * instanceSize + instanceOffset) / textureSize;
    fragColor = instanceColor;
}
