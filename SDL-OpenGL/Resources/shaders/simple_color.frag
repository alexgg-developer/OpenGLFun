#version 150 core

in vec3 fColor;

out vec4 outColor;

uniform vec3 override;

#define PRECISION 0.000001

void main()
{
    //outColor = vec4(1.0 - inColor.r, 1.0 - inColor.g, 1.0 - inColor.b, 1.0);
	//outColor = vec4(inColor, 1.0);
	//outColor = vec4(vec3(0.0, 0.0, 0.0), 1.0);
	outColor = vec4(fColor, 1.0);

	/*vec3 color = inColor;
	float isRedZero = step(-PRECISION, color.r) * (1.0 - step(PRECISION, color.r));
	float isGreenZero = step(-PRECISION, color.g) * (1.0 - step(PRECISION, color.g));
	float isBlueZero = step(-PRECISION, color.b) * (1.0 - step(PRECISION, color.b));*/

	/*if(isRedZero == 1.0 && isGreenZero == 1.0 && isBlueZero == 1.0) {
		outColor = vec4(1.0f, 0.0f, 0.0f, 1.0);
	}
	else {
		//outColor = vec4(color, 1.0);
		outColor = vec4(1.0f,1.0f, 0.0f, 1.0);
	}*/
	/*if(inColor > 0.0f) {
		outColor = vec4(1.0f, 0.0f, 0.0f, 1.0);
	}
	else {
		//outColor = vec4(color, 1.0);
		outColor = vec4(1.0f,1.0f, 0.0f, 1.0);
	}*/
	outColor = vec4(override, 1.0f);
}