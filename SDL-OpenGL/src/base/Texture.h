#pragma once
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_Image.h>
#include <string>

class Texture
{
public:
	Texture(GLuint format, bool transparent, size_t location);
	~Texture();
	bool load(const std::string &path);
	bool load(size_t width, size_t height);
	GLuint getID() const;
	size_t getLocation() const;
private:
	GLuint m_format, m_ID;
	size_t m_location, m_textureUnit;
	bool b_transparent;
};

