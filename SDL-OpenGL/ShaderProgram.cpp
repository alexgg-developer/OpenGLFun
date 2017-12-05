#include "ShaderProgram.h"
#include <glew.h>
#include <iostream>


ShaderProgram::ShaderProgram()
{
}


ShaderProgram::~ShaderProgram()
{
}


void ShaderProgram::printLog()
{
	if (glIsProgram(mID)) {
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		//Get info string length
		glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &maxLength);
		//Allocate string
		char* infoLog = new char[maxLength];
		//Get info log
		glGetProgramInfoLog(mID, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			//Print Log
			printf("%s\n", infoLog);
		}
		//Deallocate string
		delete[] infoLog;
	}
	else {
		printf("Name %d is not a program\n", mID);
	}
}
