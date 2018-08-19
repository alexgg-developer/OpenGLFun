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
	IApp() = delete;
	explicit IApp(int width, int height);
	virtual ~IApp();
	virtual bool setup() = 0;
	virtual void update();
	virtual void render() = 0;
	virtual void close();
	virtual void mainLoop() = 0;
	virtual void handleKeys(unsigned char key, int x, int y) = 0;

protected:
	int m_msElapsed, m_msLast, m_msNow;
	int m_width, m_height;
	SDL_Window* m_window = NULL;
	SDL_GLContext m_context;
};

