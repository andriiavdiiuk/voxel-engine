#version 460 core
out vec4 outputColor;
in vec3 normalVector;
in vec2 uv;
flat in uint layer;
uniform sampler2DArray texture0;

void main()
{
    outputColor = texture(texture0, vec3(uv, layer));
    //outputColor = vec4(uv, 0.0, 1.0);
}