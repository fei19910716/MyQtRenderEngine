#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 Color;

uniform mat4 m_model;
void main()
{
   gl_Position = m_model  * vec4(aPos, 1.0);
   Color = aColor;
}