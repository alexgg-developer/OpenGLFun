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

class TransformsApp: public IApp
{
public:
	TransformsApp() = delete;
	TransformsApp(int width, int height);
	~TransformsApp();

	bool setup() override;
	void update() override;
	void render() override;
	void close() override;
	void handleKeys(unsigned char key, int x, int y) override;
	void mainLoop() override;
private:
	//const float INITIAL_ROTATION_SPEED = 3.0f; //degrees / second
	const float INITIAL_ROTATION_SPEED = 0.0f; //degrees / second

	Renderer m_renderer;
	glm::mat4 m_transform;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	float m_currentSpeed, m_currentDegrees;
	bool m_isRotationActivated;

	bool initRenderer();
	bool init();
};

