#version 150 core

in vec2 position;
in vec3 color;
in vec2 inTexcoord;

out vec3 fColor;
out vec2 oTexcoord;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	oTexcoord = inTexcoord;
	fColor = color;
	mat4 changedModel = model;
    gl_Position = proj * view * changedModel * vec4(position, 0.0, 1.0);
}
