#pragma once
#include <string>
#include "glew.h"

using namespace std;

class Shader
{
public:
	enum Kind { VERTEX, FRAGMENT, GEOMETRY };

	Shader();
	Shader(const Kind kind);
	Shader(const Kind kind, const std::string path);
	~Shader();
	bool init(const Kind kind);
	bool init(const Kind kind, const std::string path);
	void logErrors() const;
	Kind getKind();
	GLuint getID() const;
	bool compile();

	friend bool operator<(const Shader &s1, const Shader &s2);
private:
	GLuint m_programID, m_ID;
	string m_source;
	Kind m_kind;

	void initShaderSource(const std::string source);
	string readSource(std::string path);
	
};

