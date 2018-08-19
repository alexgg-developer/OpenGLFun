#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <SDL.h>

#include "ShaderProgram.h"

using namespace std;

#define ASSERT(x) if (!(x)) __debugbreak();
#define ASSERT_MESSAGE(x, message) printf("assert: %s\n", #message);\
	ASSERT(x)
#define GLCall(x) DebugTools::GLClearError();\
	x;\
	ASSERT(DebugTools::GLLogCall(#x, __FILE__, __LINE__))


class DebugTools
{
public:
	/**
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message to
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	static void logSDLError(std::ostream &os, const std::string &msg);

	static void GLClearError();
	static bool GLLogCall(const char* function, const char* file, int line);
	static void printShaderLogs(shared_ptr<ShaderProgram> program);
};

