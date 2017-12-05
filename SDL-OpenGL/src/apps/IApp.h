#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>

using namespace std;

class IApp
{
public:
	IApp();
	~IApp();
	virtual void setup();
	virtual void update();
	virtual void render();
	virtual void close();

private:
	bool initGL();
	int m_width, m_height;
};

