#include "FrameBufferObject.h"
#include <iostream>

FrameBufferObject::FrameBufferObject(size_t width, size_t height):
	m_textureColorBuffer(GL_RGB, false, 0),
	m_width(width),
	m_height(height)
{
}


FrameBufferObject::~FrameBufferObject()
{
	glDeleteFramebuffers(1, &m_ID);
	glDeleteRenderbuffers(1, &m_renderBufferDepthAndStencil);
}

void FrameBufferObject::init()
{
	glGenFramebuffers(1, &m_ID);
	m_textureColorBuffer.load(m_width, m_height);
	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer.getID(), 0
	);
	glGenRenderbuffers(1, &m_renderBufferDepthAndStencil);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferDepthAndStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferDepthAndStencil
	);
}

void FrameBufferObject::activate()
{
	//possible values: GL_DRAW_FRAMEBUFFER and GL_READ_FRAMEBUFFER or GL_FRAMEBUFFER (it is both at the same time)
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void FrameBufferObject::deactivate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBufferObject::getID() const
{
	return m_ID;
}

bool FrameBufferObject::isReady()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	return status == GL_FRAMEBUFFER_COMPLETE; 
}
