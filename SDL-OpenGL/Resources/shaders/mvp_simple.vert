#version 150 core

in vec3 position;
in vec3 color;

out vec3 fColor;
out vec2 oTexcoord;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 prueba;

#define PRECISION 0.000001

void main()
{
	/*float isRedZero = step(-PRECISION, color.r) * (1.0 - step(PRECISION, color.r));
	float isGreenZero = step(-PRECISION, color.g) * (1.0 - step(PRECISION, color.g));
	float isBlueZero = step(-PRECISION, color.b) * (1.0 - step(PRECISION, color.b));

	if(isRedZero == 1.0 && isGreenZero == 1.0 && isBlueZero == 1.0) {
		fColor = vec3(1.0f, 0.0f, 0.0f);
	}
	else {
		fColor = color;
	}*/
	//fColor  = vec3(0.0f, prueba, 0.0f);
	fColor  = prueba;

    gl_Position = proj * view * model * vec4(position, 1.0);
}
