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
#include "base\FrameBufferObject.h"
#include "base\Mesh.h"

class FrameBufferApp: public IApp
{
public:
	FrameBufferApp() = delete;
	explicit FrameBufferApp(int width, int height);
	~FrameBufferApp();

	void close() override;
	void handleKeys(unsigned char key, int x, int y) override;
	void mainLoop() override;
	void render() override;
	bool setup() override;
	void update() override;
private:
	shared_ptr<ShaderProgram> m_program;
	Renderer m_renderer;
	FrameBufferObject m_frameBufferObject;
	vector<Texture> m_textures;
	unique_ptr<Mesh> m_mesh;

	glm::mat4 m_transform;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	void draw();
	bool init();
	bool initGeometry();
	bool initRenderer();
};

