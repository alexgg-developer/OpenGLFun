#include "DebugTools.h"
#include <glew.h>

void DebugTools::logSDLError(std::ostream & os, const std::string & msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void DebugTools::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool DebugTools::GLLogCall(const char* function, const char* file, int line)
{
	bool success = true;
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " "
			<< file << ":" << line << std::endl;
		success = false;
	}

	return success;
}

void DebugTools::printShaderLogs(shared_ptr<ShaderProgram> program)
{
	program->printLog();
	program->printShaderLogs();
}