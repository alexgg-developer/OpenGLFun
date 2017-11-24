#version 150 core

in vec2 position;
in vec3 color;

out vec3 fColor;

void main()
{
	fColor = color;
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}
