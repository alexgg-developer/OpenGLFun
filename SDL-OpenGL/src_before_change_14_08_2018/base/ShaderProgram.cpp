#include "ShaderProgram.h"
#include <glew.h>
#include <iostream>


ShaderProgram::ShaderProgram()
{
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::init()
{
	m_ID = glCreateProgram();
}


void ShaderProgram::printLog()
{
	if (glIsProgram(m_ID)) {
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		//Get info string length
		glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);
		//Allocate string
		char* infoLog = new char[maxLength];
		//Get info log
		glGetProgramInfoLog(m_ID, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			//Print Log
			printf("%s\n", infoLog);
		}
		//Deallocate string
		delete[] infoLog;
	}
	else {
		printf("Name %d is not a program\n", m_ID);
	}
}

void ShaderProgram::printShaderLogs()
{
	for (const Shader& shader: m_fragmentShaders) {
		shader.logErrors();
	}

	for (const Shader& shader : m_vertexShaders) {
		shader.logErrors();
	}
}

void ShaderProgram::addShader(Shader& shader)
{
	Shader::Kind kind = shader.getKind();
	switch (kind) {
	case Shader::Kind::VERTEX: {
		m_vertexShaders.insert(shader);
		break;
	}
	case Shader::Kind::FRAGMENT: {
		m_fragmentShaders.insert(shader);
		break;
	}
	case Shader::Kind::GEOMETRY:
		m_geometryShaders.insert(shader);
		break;
	}
	glAttachShader(m_ID, shader.getID());
}

void ShaderProgram::removeShader(Shader& shader)
{
	Shader::Kind kind = shader.getKind();
	switch (kind) {
	case Shader::Kind::VERTEX: {
		m_vertexShaders.erase(shader);
		break;
	}
	case Shader::Kind::FRAGMENT: {
		m_fragmentShaders.erase(shader);
		break;
	}
	case Shader::Kind::GEOMETRY:
		m_geometryShaders.erase(shader);
		break;
	}
}

bool ShaderProgram::link()
{
	glLinkProgram(m_ID);
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE) {
		printf("Error linking program %d!\n", m_ID);
		printLog();
		return false;
	}

	return true;
}

void ShaderProgram::activate()
{
	glUseProgram(m_ID);
}

void ShaderProgram::deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::sampleTexture(std::string attribName, int slotNumber)
{
	glUniform1i(glGetUniformLocation(m_ID, attribName.c_str()), slotNumber);
}

void ShaderProgram::bindFragmentOutputWithBuffer(unsigned int buffer, std::string fragmentOutputName)
{
	glBindFragDataLocation(m_ID, buffer, fragmentOutputName.c_str());
}

size_t ShaderProgram::getAttributeLocation(std::string attributeName)
{
	return glGetAttribLocation(m_ID, attributeName.c_str());
}

size_t ShaderProgram::getUniformLocation(std::string uniformName)
{
	return glGetUniformLocation(m_ID, uniformName.c_str());
}

void ShaderProgram::clean()
{
	glDeleteProgram(m_ID);
}

int ShaderProgram::getID() const
{
	return m_ID;
}
