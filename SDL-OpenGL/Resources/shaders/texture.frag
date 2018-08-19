#version 150 core

in vec3 fColor;
in vec2 oTexcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    outColor = texture(tex, oTexcoord) * vec4(fColor, 1.0);
	//outColor = texture(tex, oTexcoord);
}