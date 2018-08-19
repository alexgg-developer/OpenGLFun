#include "Texture.h"
#include <iostream>

Texture::Texture(GLuint format, bool transparent, size_t location) :
	m_format(format),
	b_transparent(transparent),
	m_location(location)
{
	switch (location) {
	case 0:
		m_textureUnit = GL_TEXTURE0;
		break;
	case 1:
		m_textureUnit = GL_TEXTURE1;
		break;
	default:
		m_textureUnit = 0;
		break;
	}
}


Texture::~Texture()
{
}

bool Texture::load(size_t width, size_t height)
{
	bool success = true;

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	return success;
}

GLuint Texture::getID() const
{
	return m_ID;
}

bool Texture::load(const std::string &path)
{
	glActiveTexture(m_textureUnit);
	bool success = true;
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		success = false;
	}
	else {
		SDL_Surface* textureSurface = IMG_Load(path.c_str());
		if (textureSurface == nullptr) {
			std::cout << "Unable to load image " << path.c_str() << " SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSurface->w, textureSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSurface->pixels);
			glTexImage2D(GL_TEXTURE_2D, 0, m_format, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, m_format, GL_UNSIGNED_BYTE, textureSurface->pixels);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, textureSurface->pixels);
			/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
			//glBindTexture(GL_TEXTURE_2D, 0);
		}
		SDL_FreeSurface(textureSurface);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glActiveTexture(0);

	return success;
}

size_t Texture::getLocation() const
{
	return m_location;
}

