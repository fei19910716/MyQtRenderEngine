#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 in_color;
in vec3 in_pos;
uniform vec4 u_color;
uniform sampler2D u_texture0;
void main()
{
   vec4 tex_color = texture(u_texture0, TexCoord);
   FragColor = mix(u_color,tex_color,0.5);
   // FragColor = vec4(TexCoord.x,TexCoord.y,0.0,1.0);
   // FragColor = vec4(in_color,1.0);
}