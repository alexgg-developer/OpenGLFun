#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(): m_VBO(0), m_VAO(0), m_IBO(0)
{
}


Renderer::~Renderer()
{
}

bool Renderer::init()
{
	bool success = true;
	//Alpha test
	/*glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	
	m_program->init();
	Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/texture.vert");
	if (!vertexShader.compile()) {
		return false;
	}
	m_program->addShader(vertexShader);
	Shader fragmentShader(Shader::Kind::FRAGMENT, "Resources/shaders/blend.frag");
	if (!fragmentShader.compile()) {
		return false;
	}
	m_program->addShader(fragmentShader);
	m_program->link();
	m_program->activate();

	Texture t0(GL_RGB, false, 0);
	t0.load("Resources/imgs/nehe.png");
	glUniform1i(m_program->getUniformLocation("texKitten"), t0.getLocation());

	Texture t1(GL_RGB, false, 1);
	t1.load("Resources/imgs/strawberry.jpg");
	glUniform1i(m_program->getUniformLocation("texPuppy"), t1.getLocation());

	m_program->bindFragmentOutputWithBuffer(0, "outColor");
	m_attributeLocations["position"] = m_program->getAttributeLocation("position");
	m_attributeLocations["color"] = m_program->getAttributeLocation("color");
	m_attributeLocations["inTexcoord"] = m_program->getAttributeLocation("inTexcoord");

	if (m_attributeLocations["position"] != -1) {
		//Initialize clear color
		glClearColor(0.f, 1.f, 1.f, 1.f);
		//VBO data
		//position vec2 color vec3 texcoord vec2
		
		vector<float> vertices = {
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
		};
		/*float vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
		};*/
		//IBO data
		/*GLuint indexData[] = {
			0, 1, 2,
			2, 3, 0
		};*/
		vector<size_t> indexData = {
			0, 1, 2,
			2, 3, 0
		};

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		//Create VBO
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		//Create IBO
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), &indexData, GL_STATIC_DRAW);

		glUseProgram(0);
	}

	return success;
}

/**
* Pre:
*	program: the program has been inited, linked and activated beforehand
*/
bool Renderer::init(unique_ptr<ShaderProgram> program)
{
	bool success = true;
	m_program = std::move(program); 

	/*Texture t0(GL_RGB, false, 0);
	t0.load("Resources/imgs/nehe.png");
	glUniform1i(m_program->getUniformLocation("texKitten"), t0.getLocation());

	Texture t1(GL_RGB, false, 1);
	t1.load("Resources/imgs/strawberry.jpg");
	glUniform1i(m_program->getUniformLocation("texPuppy"), t1.getLocation());*/
	
	m_program->bindFragmentOutputWithBuffer(0, "outColor");
	m_attributeLocations["position"] = m_program->getAttributeLocation("position");
	m_attributeLocations["color"] = m_program->getAttributeLocation("color");
	//m_attributeLocations["inTexcoord"] = m_program->getAttributeLocation("inTexcoord");

	if (m_attributeLocations["position"] != -1) {
		//Initialize clear color
		glClearColor(0.f, 1.f, 1.f, 1.f);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		//Create VBO
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//size_t size = m_vertices[0].size() * sizeof(float);
		//glBufferData(GL_ARRAY_BUFFER, size, &m_vertices[0], GL_STATIC_DRAW);
		size_t size = m_vertices[0].size() * sizeof(float);
		glBufferData(GL_ARRAY_BUFFER, size, &m_vertices[0][0], GL_STATIC_DRAW);
		//Create IBO
		if (m_indices.size() > 0) {
			size = m_indices[0].size() * sizeof(size_t);
			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &m_indices[0][0], GL_STATIC_DRAW);
		}
	}

	return success;
}

void Renderer::clean()
{
	m_program->clean();
	glDeleteBuffers(1, &m_VBO);
}

void Renderer::activateProgram()
{
	m_program->activate();
}

void Renderer::addGeometry(vector<float>&& vertices)
{
	m_vertices.push_back(std::move(vertices));
}

void Renderer::addGeometry(vector<float>&& vertices, vector<size_t>&& indices)
{
	m_vertices.push_back(std::move(vertices));
	m_indices.push_back(std::move(indices));
}

void Renderer::addGeometry(vector<float> vertices)
{
	m_vertices.push_back(vertices);
}

void Renderer::deactivateProgram()
{
	m_program->deactivate();
}

void Renderer::addUniform(const string & name)
{
	GLuint uniformLocation = m_program->getUniformLocation(name);
	m_uniformLocations[name] = uniformLocation;
}

void Renderer::addAttribute(const string & name)
{
	GLuint attributeLocation = m_program->getAttributeLocation(name);
	m_attributeLocations[name] = attributeLocation;
}

void Renderer::setUniformValue(const string& name, GLuint value)
{
	glUniform1i(m_uniformLocations[name], value);
}

void Renderer::setUniformValue(const string & name, float value)
{
	//int uniformLocation = m_uniformLocations[name];
	glUniform1f(m_uniformLocations[name], value);
}

void Renderer::setUniformValue(const string & name, float x, float y, float z)
{
	glUniform3f(m_uniformLocations[name], x, y, z);
}

void Renderer::setUniformValue(const string & name, glm::vec3& value)
{
	//glUniform3f(m_uniformLocations[name], value.x, value.y, value.z);
	glUniform3fv(m_uniformLocations[name], 1, glm::value_ptr(value));
}

void Renderer::setUniformValue(const string & name, const int numberMatrices, GLboolean transpose, glm::mat4 value)
{
	glUniformMatrix4fv(m_uniformLocations[name], numberMatrices, transpose, glm::value_ptr(value));
}

void Renderer::draw()
{
	//glBindTexture(GL_TEXTURE_2D, gTexture0);
	//glBindTexture(GL_TEXTURE_2D, gTexture1);
	/*GLint uniColor = glGetUniformLocation(gProgramID, "inColor");
	auto t_now = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
	glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, (cos(time * 4.0f) + 1.0f) / 2.0f, (sin(time * 4.0f) + 1.0f) / 2.0f);*/
	//Enable vertex position
	glEnableVertexAttribArray(m_attributeLocations["position"]);
	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(m_attributeLocations["position"], 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(m_attributeLocations["color"]);
	glVertexAttribPointer(m_attributeLocations["color"], 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	glVertexAttribPointer(m_attributeLocations["inTexcoord"], 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//Disable vertex position
	glDisableVertexAttribArray(m_attributeLocations["position"]);
	glDisableVertexAttribArray(m_attributeLocations["color"]);
	glDisableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	//Unbind program
	m_program->deactivate();
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw3D()
{
	//glBindTexture(GL_TEXTURE_2D, gTexture0);
	//glBindTexture(GL_TEXTURE_2D, gTexture1);
	/*GLint uniColor = glGetUniformLocation(gProgramID, "inColor");
	auto t_now = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
	glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, (cos(time * 4.0f) + 1.0f) / 2.0f, (sin(time * 4.0f) + 1.0f) / 2.0f);*/
	//Enable vertex position
	glEnableVertexAttribArray(m_attributeLocations["position"]);
	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(m_attributeLocations["position"], 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(m_attributeLocations["color"]);
	glVertexAttribPointer(m_attributeLocations["color"], 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	glVertexAttribPointer(m_attributeLocations["inTexcoord"], 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//Disable vertex position
	glDisableVertexAttribArray(m_attributeLocations["position"]);
	glDisableVertexAttribArray(m_attributeLocations["color"]);
	glDisableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	//Unbind program
	m_program->deactivate();
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawArray()
{
	//Enable vertex position
	glEnableVertexAttribArray(m_attributeLocations["position"]);
	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(m_attributeLocations["position"], 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(m_attributeLocations["color"]);
	glVertexAttribPointer(m_attributeLocations["color"], 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	glVertexAttribPointer(m_attributeLocations["inTexcoord"], 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//Set index data and render
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(m_attributeLocations["position"]);
	glDisableVertexAttribArray(m_attributeLocations["color"]);
	glDisableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	//Unbind program
	m_program->deactivate();
}

void Renderer::drawArrayWithStencil()
{
	//Enable vertex position
	glEnableVertexAttribArray(m_attributeLocations["position"]);
	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(m_attributeLocations["position"], 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(m_attributeLocations["color"]);
	glVertexAttribPointer(m_attributeLocations["color"], 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	glVertexAttribPointer(m_attributeLocations["inTexcoord"], 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//Set index data and render
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glEnable(GL_STENCIL_TEST);
	// Draw floor
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 36, 6);

	// Draw cube reflection
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(
		glm::translate(model, glm::vec3(0, 0, -1)),
		glm::vec3(1, 1, -1)
	);

	setUniformValue("model", 1, GL_FALSE, model);

	setUniformValue("overrideColor", glm::vec3(0.3f, 0.3f, 0.3f));
	//glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

	glDisable(GL_STENCIL_TEST);


	glDisableVertexAttribArray(m_attributeLocations["position"]);
	glDisableVertexAttribArray(m_attributeLocations["color"]);
	glDisableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	//Unbind program
	m_program->deactivate();
}

GLuint Renderer::getVBO()
{
	return m_VBO;
}

GLuint Renderer::getAttributeLocation(const string & attribute)
{
	return m_attributeLocations[attribute];
}

void Renderer::printShaderLogs()
{
	m_program->printLog();
	m_program->printShaderLogs();
}
