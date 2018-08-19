#version 150 core

in vec3 fColor;
in vec2 oTexcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    
	vec2 flippedTexcoord;
	//flippedTexcoord.xy = 1.0f - oTexcoord.xy;
	flippedTexcoord.x = oTexcoord.x;
	flippedTexcoord.y = 1.0f - oTexcoord.y;
	//outColor = texture(tex, flippedTexcoord);
	outColor = texture(tex, flippedTexcoord) * vec4(fColor, 1.0);
}