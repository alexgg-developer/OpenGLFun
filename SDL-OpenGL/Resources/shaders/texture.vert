#version 150 core

in vec2 position;
in vec3 color;
in vec2 inTexcoord;

out vec3 fColor;
out vec2 oTexcoord;

void main()
{
	oTexcoord = inTexcoord;
	fColor = color;
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}
