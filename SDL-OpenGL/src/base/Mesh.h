#pragma once

#include <glew.h>

#include <vector>
#include <memory>

#include "base\IRenderable.h"
#include "base\VertexBufferLayout.h"

using namespace std;

class Mesh: public IRenderable
{
public:
	Mesh(bool useIndices = true);
	virtual ~Mesh();
	void addIndices(vector<size_t>& indices);
	void addVertices(vector<float>& vertices);
	void init();
	void setVertexBufferLayout(unique_ptr<VertexBufferLayout>& vertexBufferLayout);
	void setVertexBufferLayout(VertexBufferLayout&& vertexBufferLayout);

	virtual void draw() const;
private:
	GLuint m_VBO, m_VAO, m_IBO;
	unique_ptr<VertexBufferLayout> m_vertexBufferLayout;
	vector<size_t> m_indices;
	vector<float> m_vertices;

	bool b_useIndices;
};

