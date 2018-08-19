#include "Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>

Shader::Shader()
{
}

Shader::Shader(const Kind kind)
{
	init(kind);
}

Shader::Shader(const Kind kind, const string path)
{
	init(kind, path);
}

Shader::~Shader()
{
}

void Shader::initShaderSource(const std::string source)
{
	m_source = source;
	const char* src = m_source.c_str();
	glShaderSource(m_ID, 1, &src, NULL);
}

bool Shader::init(const Kind kind)
{
	m_kind = kind;
	switch (kind) {
	case VERTEX: {
		m_ID = glCreateShader(GL_VERTEX_SHADER);
		initShaderSource("#version 130\nin vec2 LVertexPos2D; out vec2 texcoords; void main() { texcoords = LVertexPos2D.xy + 0.5; texcoords.y = 1.0 - texcoords.y; gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }");		
		break;
	}
	case FRAGMENT: {
		m_ID = glCreateShader(GL_FRAGMENT_SHADER);
		initShaderSource("#version 130\nin vec2 texcoords; uniform sampler2D teximg; out vec4 LFragment; void main() { LFragment = texture(teximg, texcoords.xy); }");		
		break;
	}	
	case GEOMETRY:
		m_ID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}
	return true;
}

bool Shader::init(const Kind kind, const std::string path)
{
	m_kind = kind;
	switch (kind) {
	case VERTEX: {
		m_ID = glCreateShader(GL_VERTEX_SHADER);
		break;
	}
	case FRAGMENT: {
		m_ID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	case GEOMETRY:
		m_ID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}
	string source = readSource(path);
	initShaderSource(source);

	return true;
}

string Shader::readSource(std::string path)
{
	std::ostringstream sstream;
	ifstream fs(path);
	sstream << fs.rdbuf();
	return std::string(sstream.str());
}

void Shader::logErrors() const
{
	GLint status;
	glGetShaderiv(m_ID, GL_COMPILE_STATUS, &status);
	int infoLogLength = 0;
	int maxLength = infoLogLength;
	//char buffer[512];
	//glGetShaderInfoLog(Shader, 512, NULL, buffer);
	//Get info string length
	glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);
	char* infoLog = new char[maxLength];
	glGetShaderInfoLog(m_ID, maxLength, &infoLogLength, infoLog);
	if (maxLength > 0) {
		std::cout << "--- Shader compile output ---" << std::endl;
		std::cout << infoLog << std::endl;
		std::cout << "--- --- ---" << std::endl;
	}
	delete[] infoLog;
}

Shader::Kind Shader::getKind()
{
	return m_kind;
}

bool Shader::compile()
{
	bool success = true;
	glCompileShader(m_ID);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(m_ID, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE) {
		printf("Unable to compile vertex shader %d!\n", m_ID);
		logErrors();
		success = false;
	}

	return success;
}

GLuint Shader::getID() const
{
	return m_ID;
}

bool operator<(const Shader & s1, const Shader & s2)
{
	return s1.getID() < s2.getID();
}
