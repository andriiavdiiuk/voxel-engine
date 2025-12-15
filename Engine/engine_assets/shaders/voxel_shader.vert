#version 460 core
layout(location = 0) in uvec2 packedVertex;
flat out uint layer;
out vec3 normalVector;
out vec2 uv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 chunkPosition;
uniform int chunkSize;

vec2 UV_COORDS[4] = vec2[](
    vec2(0.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 0.0),
    vec2(1.0, 1.0)
);

const vec3 NORMAlS[6] = vec3[](
    vec3(0.0,0.0,1.0),
    vec3(0.0,0.0,-1.0),
    vec3(0.0,1.0,0.0),
    vec3(0.0,-1.0,0.0),
    vec3(1.0,0.0,0.0),
    vec3(-1.0,0.0,0.0)
);

void main()
{ 
    uint x = packedVertex.x & 31; 
    uint y  = (packedVertex.x >> 5) & 31;
    uint z  =  (packedVertex.x >> 10) & 31;
    uint face = (packedVertex.x >> 15) & 7;
    uint uv_index = (packedVertex.x >> 18) & 3; 
    layer = packedVertex.y;

    uv = UV_COORDS[int(uv_index)];
    vec3 worldPos = vec3(x,y,z) + chunkPosition * float(chunkSize);
    normalVector = NORMAlS[int(face)];
    gl_Position = projection * view * vec4(worldPos, 1.0);

}