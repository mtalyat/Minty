#version 450

#extension GL_EXT_nonuniform_qualifier : require

layout(binding = 0) uniform Canvas {
    int width;
    int height;
    int unused0;
    int unused1;
} canvas;

layout(location = 0) in vec4 position; // (x, y, width, height)
layout(location = 1) in vec4 uv; // (x, y, width, height)
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 pivot; // (x, y)
layout(location = 4) in float depth;
layout(location = 5) in float rotation; // radians

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    //gl_VertexIndex
    vec2 vertices[6] =
    {
        vec2(0.0, 0.0),
        vec2(1.0, 0.0),
        vec2(0.0, 1.0),
        vec2(0.0, 1.0),
        vec2(1.0, 0.0),
        vec2(1.0, 1.0)
    };

    // get position for the vertex
    vec2 pos = vertices[gl_VertexIndex % 6];

    // get the position relative to the pivot
    vec2 relativePos = (pos - pivot) * vec2(position.z, position.w);

    // apply rotation
    if(rotation != 0.0)
    {
        float cosR = cos(rotation);
        float sinR = sin(rotation);

        // rotate around pivot
        relativePos = vec2(
            relativePos.x * cosR - relativePos.y * sinR,
            relativePos.x * sinR + relativePos.y * cosR
        );
    }

    gl_Position = vec4(
        (position.x + relativePos.x) / canvas.width * 2.0 - 1.0, 
        (position.y + relativePos.y) / canvas.height * 2.0 - 1.0, 
        depth, 
        1.0);
    
    fragColor = color;
    fragTexCoord = vec2(uv.x + pos.x * uv.z, uv.y + pos.y * uv.w);
}