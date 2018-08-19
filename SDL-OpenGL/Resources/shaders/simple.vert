#version 150 core

in vec2 position;
in vec3 color;

#define PRECISION 0.000001

out vec3 fColor;

void main()
{
	float isRedZero = step(-PRECISION, color.r) * (1.0 - step(PRECISION, color.r));
	float isGreenZero = step(-PRECISION, color.g) * (1.0 - step(PRECISION, color.g));
	float isBlueZero = step(-PRECISION, color.b) * (1.0 - step(PRECISION, color.b));

	if(isRedZero == 1.0 && isGreenZero == 1.0 && isBlueZero == 1.0) {
		fColor = vec3(1.0f, 0.0f, 0.0f);
	}
	else {
		fColor = color;
	}
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}
