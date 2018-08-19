#include "Mesh.h"

Mesh::Mesh(bool useIndices): b_useIndices(useIndices), m_VBO(0), m_VAO(0), m_IBO(0)
{
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
}

void Mesh::addVertices(vector<float>& vertices)
{
	m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
}

void Mesh::setVertexBufferLayout(unique_ptr<VertexBufferLayout>& vertexBufferLayout)
{
	m_vertexBufferLayout = std::move(vertexBufferLayout);	
}

void Mesh::setVertexBufferLayout(VertexBufferLayout&& vertexBufferLayout)
{
	m_vertexBufferLayout = std::make_unique<VertexBufferLayout>(vertexBufferLayout);
}

void Mesh::addIndices(vector<size_t>& indices)
{
	m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

void Mesh::draw() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	const auto& elements = m_vertexBufferLayout->getElements();
	int i = 0;
	int stride = 0;
	for (const auto& element : elements) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, m_vertexBufferLayout->getStride(), (const void*)stride);
		++i;
		stride += element.count * element.getSizeOfType(element.type);
	}
	/*glEnableVertexAttribArray(program.getAttributeLocation("position"));
	glVertexAttribPointer(program.getAttributeLocation("position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(program.getAttributeLocation("color"));
	glVertexAttribPointer(program.getAttributeLocation("color"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_renderer.getAttributeLocation("inTexcoord"));
	glVertexAttribPointer(m_renderer.getAttributeLocation("inTexcoord"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));*/
	//Set index data and render
	if (!b_useIndices) {
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Mesh::init()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	//Create VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//size_t size = m_vertices[0].size() * sizeof(float);
	//glBufferData(GL_ARRAY_BUFFER, size, &m_vertices[0], GL_STATIC_DRAW);
	size_t size = m_vertices.size() * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, size, &m_vertices[0], GL_STATIC_DRAW);
}
