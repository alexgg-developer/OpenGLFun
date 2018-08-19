#pragma once
#include "glew.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <vector>
#include <map>
#include <memory>

#include <glm/glm.hpp>

using namespace std;

class Renderer
{
public:
	Renderer();
	~Renderer(); 
	void activateProgram();
	void addAttribute(const string & name);
	void addGeometry(vector<float> vertices);
	void addGeometry(vector<float>&& vertices);
	void addGeometry(vector<float>&& vertices, vector<size_t>&& indices);
	void addUniform(const string& name);
	void clean();
	void deactivateProgram();
	void draw();
	void draw3D();
	void drawArray();
	void drawArrayWithStencil();
	GLuint getVBO();
	GLuint getAttributeLocation(const string& attribute);
	bool init();
	bool init(unique_ptr<ShaderProgram> program);
	void printShaderLogs();
	void setUniformValue(const string& name, GLuint value);
	void setUniformValue(const string& name, float value);
	void setUniformValue(const string & name, float x, float y, float z);
	void setUniformValue(const string & name, glm::vec3& value);
	void setUniformValue(const string& name, const int numberMatrices, GLboolean transpose, glm::mat4 value);
private:
	GLuint m_VBO, m_VAO, m_IBO;
	unique_ptr<ShaderProgram> m_program;
	vector<Texture> m_textures;
	map<string, GLuint> m_attributeLocations;
	map<string, size_t> m_uniformLocations;
	vector<vector<size_t>> m_indices;
	vector<vector<float>> m_vertices;
};

