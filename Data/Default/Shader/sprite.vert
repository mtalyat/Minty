#version 450

#extension GL_EXT_nonuniform_qualifier : require

layout(binding = 0) uniform Camera {
    mat4 camera;
} camera;

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
    vec2 pos = quadPosition;

    // Convert the shared 0..1 quad into pixel space, then scale to world units.
    vec2 local = (pos * instanceSize - instancePivot) * instanceScale;

    // set position
    gl_Position = camera.camera * instanceTransform * vec4(local.x, local.y * -1, 0.0, 1.0);
    
    // set texture coordinates
    vec2 texCoord = quadTexCoord;
    if((instanceFlags & 0x1) != 0)
    {
        // flip X
        texCoord.x = 1.0 - texCoord.x;
    }
    if ((instanceFlags & 0x2) != 0)
    {
        // flip Y
        texCoord.y = 1.0 - texCoord.y;
    }
    vec2 textureSize = max(instanceTextureSize, vec2(1.0));
    fragTexCoord = (texCoord * instanceSize + instanceOffset) / textureSize;

    // set color
    fragColor = instanceColor;
}