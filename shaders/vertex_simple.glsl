#version 460 core

layout (location = 0) in vec2 position;

out vec2 frag_position; 

void main()
{
    frag_position = position;
    gl_Position = vec4(position, 0.0, 1.0);
}


