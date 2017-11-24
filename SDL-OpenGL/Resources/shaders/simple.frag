#version 150 core

//uniform vec3 inColor;
in vec3 fColor;

out vec4 outColor;

void main()
{
    //outColor = vec4(1.0 - fColor.r, 1.0 - fColor.g, 1.0 - fColor.b, 1.0);
	outColor = vec4(fColor, 1.0);
}