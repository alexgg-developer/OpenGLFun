#include "Shader.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::initShaderSource(const std::string source)
{
	mShaderSource = source;
	glShaderSource(mID, 1, &mShaderSource.c_str(), NULL);
}

bool Shader::init(const KindOfShader kind)
{
	switch (kind) {
	case VERTEX: {
		mID = glCreateShader(GL_VERTEX_SHADER);
		initShaderSource("#version 130\nin vec2 LVertexPos2D; out vec2 texcoords; void main() { texcoords = LVertexPos2D.xy + 0.5; texcoords.y = 1.0 - texcoords.y; gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }");		
		break;
	}
	case FRAGMENT: {
		mID = glCreateShader(GL_FRAGMENT_SHADER);
		initShaderSource("#version 130\nin vec2 texcoords; uniform sampler2D teximg; out vec4 LFragment; void main() { LFragment = texture(teximg, texcoords.xy); }");		
		break;
	}	
	case GEOMETRY:
		mID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}
	return true;
}

bool Shader::init(const KindOfShader kind, const std::string path)
{
	switch (kind) {
	case VERTEX: {
		mID = glCreateShader(GL_VERTEX_SHADER);
		break;
	}
	case FRAGMENT: {
		mID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	case GEOMETRY:
		mID = glCreateShader(GL_GEOMETRY_SHADER);
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

void Shader::logErrors()
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	int infoLogLength = 0;
	int maxLength = infoLogLength;
	//char buffer[512];
	//glGetShaderInfoLog(Shader, 512, NULL, buffer);
	//Get info string length
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
	char* infoLog = new char[maxLength];
	glGetShaderInfoLog(mID, maxLength, &infoLogLength, infoLog);
	std::cout << "--- Shader compile output ---" << std::endl;
	std::cout << infoLog << std::endl;
	std::cout << "--- --- ---" << std::endl;
	delete[] infoLog;

}