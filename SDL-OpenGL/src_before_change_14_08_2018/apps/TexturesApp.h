#pragma once
#define GLEW_STATIC
#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <SDL_image.h>


#include "apps\IApp.h"
#include "base\Renderer.h"

class TexturesApp: public IApp
{
public:
	TexturesApp() = delete;
	TexturesApp(int width, int height);
	~TexturesApp();

	bool setup() override;
	void update() override;
	void render() override;
	void close() override;
	void handleKeys(unsigned char key, int x, int y) override;
	void mainLoop() override;
private:
	Renderer m_renderer;

	bool initRenderer();
	bool initGeometry();
};

