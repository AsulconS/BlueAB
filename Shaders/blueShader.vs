#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// blue = (0.13f, 0.25f, 0.75f, 1.0f)
void main()
{
    mat4 transform = projection * view * model;
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
}
