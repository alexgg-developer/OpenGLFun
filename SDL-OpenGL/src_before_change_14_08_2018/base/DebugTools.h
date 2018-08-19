#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

class DebugTools
{
public:
	/**
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message to
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	static void logSDLError(std::ostream &os, const std::string &msg);
};

