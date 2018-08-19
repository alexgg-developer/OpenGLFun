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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "apps\IApp.h"
#include "base\Renderer.h"

class StencilApp: public IApp
{
public:
	StencilApp() = delete;
	explicit StencilApp(int width, int height);
	~StencilApp();

	void close() override;
	void handleKeys(unsigned char key, int x, int y) override;
	void mainLoop() override;
	void render() override;
	bool setup() override;
	void update() override;
private:
	Renderer m_renderer;
	glm::mat4 m_transform;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	bool init();
	bool initGeometry();
	bool initRenderer();
};

