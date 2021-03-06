#version 150 core

in vec3 fColor;
in vec2 oTexcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;

void main()
{
    vec4 colKitten = texture(texKitten, oTexcoord);
	//vec4 colKitten = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 colPuppy = texture(texPuppy, oTexcoord);
	//vec4 colPuppy = vec4(1.0, 1.0, 1.0, 1.0);
    outColor = mix(colKitten, colPuppy, 0.5);
}