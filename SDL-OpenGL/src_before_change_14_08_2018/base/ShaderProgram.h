#pragma once
#include <set>

#include "Shader.h"

using namespace std;

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void init();
	void printShaderLogs();
	void printLog();
	void addShader(Shader& shader);
	void removeShader(Shader& shader);
	bool link();
	void activate();
	void deactivate();
	void sampleTexture(std::string attribName, int slotNumber);
	void bindFragmentOutputWithBuffer(unsigned int buffer, std::string fragmentOutputName);
	size_t getAttributeLocation(std::string attributeName);
	size_t getUniformLocation(std::string uniformName);
	void clean();
	int getID() const;
private:
	int m_ID;
	set<Shader> m_vertexShaders;
	set<Shader> m_fragmentShaders;
	set<Shader> m_geometryShaders;
};

