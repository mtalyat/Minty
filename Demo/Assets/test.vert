#version 450

layout(binding = 0) uniform Camera
{
    mat4 camera;
} camera;

layout(push_constant) uniform DrawObject
{
    mat4 transform;
} object;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = camera.camera * object.transform * vec4(inPosition, 1.0);
    fragNormal = inNormal;
    fragTexCoord = inTexCoord;
}