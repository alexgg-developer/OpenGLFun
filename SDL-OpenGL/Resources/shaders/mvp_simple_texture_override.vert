#version 150 core

in vec3 position;
in vec3 color;
in vec2 inTexcoord;

out vec3 fColor;
out vec2 oTexcoord;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 overrideColor;

void main()
{
	oTexcoord = inTexcoord;
	fColor = overrideColor * color;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
