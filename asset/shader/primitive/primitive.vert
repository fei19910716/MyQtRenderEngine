#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 Color;

uniform mat4 m_projection;
uniform mat4 m_view;
uniform mat4 m_model;
void main()
{
   gl_Position = m_projection * m_view * m_model  * vec4(aPos, 1.0);
   Color = aColor;
}