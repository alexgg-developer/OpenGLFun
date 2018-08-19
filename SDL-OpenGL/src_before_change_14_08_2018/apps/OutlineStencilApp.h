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
#include "base\Primitives\CubePrimitive.h"

//algorithm taken from: http://www.flipcode.com/archives/Object_Outlining.shtml

class OutlineStencilApp: public IApp
{
public:
	glm::vec3 RED_COLOR, BLUE_COLOR, GREEN_COLOR;
	OutlineStencilApp() = delete;
	explicit OutlineStencilApp(int width, int height);
	~OutlineStencilApp();

	void close() override;
	void handleKeys(unsigned char key, int x, int y) override;
	void mainLoop() override;
	void render() override;
	bool setup() override;
	void update() override;
private:
	CubePrimitive m_cube;
	Renderer m_renderer;
	glm::mat4 m_transform;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	bool init();
	bool initGeometry();
	bool initRenderer();
	void drawArray();
	void drawOutlining();
};

