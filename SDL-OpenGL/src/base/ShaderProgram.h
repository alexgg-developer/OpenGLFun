#pragma once
#include <set>
#include <map>

#include <glm/glm.hpp>

#include "Shader.h"

using namespace std;

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void activate();
	void addAttribute(const string & name);
	void addShader(Shader& shader);
	void addUniform(const string& name);
	void bindFragmentOutputWithBuffer(unsigned int buffer, std::string fragmentOutputName);
	void clean();
	void deactivate();
	size_t getAttributeLocation(std::string attributeName);
	int getID() const;
	size_t getUniformLocation(std::string uniformName);
	void init();
	bool link();
	void printShaderLogs();
	void printLog();
	void removeShader(Shader& shader);
	void sampleTexture(std::string attribName, int slotNumber);
	void setUniformValue(const string& name, GLuint value);
	void setUniformValue(const string& name, float value);
	void setUniformValue(const string & name, float x, float y, float z);
	void setUniformValue(const string & name, glm::vec3& value);
	void setUniformValue(const string& name, const int numberMatrices, GLboolean transpose, glm::mat4 value);
private:
	int m_ID;
	set<Shader> m_vertexShaders;
	set<Shader> m_fragmentShaders;
	set<Shader> m_geometryShaders;

	map<string, GLuint> m_attributeLocations;
	map<string, size_t> m_uniformLocations;
};

