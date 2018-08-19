#version 150 core

in vec3 fColor;
in vec2 oTexcoord;

out vec4 outColor;

uniform float time;
uniform sampler2D texKitten;
uniform sampler2D texPuppy;

void main()
{
	vec4 colKitten;
	if(oTexcoord.y < 0.5) {
		colKitten = texture(texKitten, oTexcoord);
	}
	else {
		//float factor = (sin(time + oTexcoord.y * 64)) * 0.1;
		float factor = sin(oTexcoord.y * 60.0 + time * 2.0) / 30.0;
		vec2 reflectedCoord = vec2(oTexcoord.x + factor, 1.0 - oTexcoord.y);
		colKitten = texture(texKitten, reflectedCoord) * vec4(0.7, 0.7, 1.0, 1.0);
	}
    outColor = colKitten;
}