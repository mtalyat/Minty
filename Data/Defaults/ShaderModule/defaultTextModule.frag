#version 450

#extension GL_EXT_nonuniform_qualifier : require

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

void main() {
    vec4 texColor = texture(texSampler, fragTexCoord);

    // get average color from texture
    float averageColor = (texColor.r + texColor.g + texColor.b) / 3.0;

    // get the alpha value to use
    float alpha = averageColor;

    // ignore invisible pixels
    if(alpha == 0.0) discard;

    outColor = vec4(texColor.r * fragColor.r, texColor.g * fragColor.g, texColor.b * fragColor.b, alpha);
}