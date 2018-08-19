#pragma once
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_Image.h>
#include <string>

#include "Texture.h"

class FrameBufferObject
{
public:
	explicit FrameBufferObject(size_t width, size_t height);
	~FrameBufferObject();

	void activate();
	void deactivate();
	GLuint getID() const;
	void init();
	bool isReady();
private:
	GLuint m_ID, m_renderBufferDepthAndStencil;
	size_t m_width, m_height;
	Texture m_textureColorBuffer;

};

