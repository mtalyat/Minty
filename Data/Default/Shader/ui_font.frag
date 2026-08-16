#version 450

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

void main() {
    vec4 sampled = texture(texSampler, fragTexCoord);
    float rgbMask = dot(sampled.rgb, vec3(0.299, 0.587, 0.114));
    float alphaMask = sampled.a;

    // Support both common font atlas layouts:
    // 1) alpha contains coverage, RGB arbitrary
    // 2) RGB contains monochrome coverage, alpha opaque
    float mask = alphaMask;
    if (alphaMask >= 0.999) {
        mask = rgbMask;
    }

    outColor = vec4(fragColor.rgb, fragColor.a * mask);

    if (outColor.a <= 0.01) {
        discard;
    }
}
