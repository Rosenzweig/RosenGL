#version 150

in vec3 a_position;
in vec3 a_color;
out vec4 Color; 

void main()
{
	Color = vec4(a_color, 1.0);
	gl_Position = vec4(a_position, 1.0);
}