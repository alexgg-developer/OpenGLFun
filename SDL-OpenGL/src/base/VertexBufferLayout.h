#pragma once

#include <glew.h>

#include <vector>
#include "DebugTools.h"


using namespace std;


class VertexBufferLayout
{
public:
	struct Element
	{
		size_t count;
		//size_t stride;
		//size_t positionData;
		size_t type;
		static unsigned int getSizeOfType(GLenum type)
		{
			switch (type) {
			case GL_FLOAT: return sizeof(GLfloat);
			}
			ASSERT_MESSAGE(false, "Type not added or wrong type");
			//static_assert(false);
			return 0;
		}
	};

	VertexBufferLayout();
	~VertexBufferLayout();
	template <typename T>
	void add(size_t count)
	{
		static_assert(false, "Wrong or not added specialization for vertex buffer layout");
	}
	template <>
	void add<float>(size_t count)
	{
		m_elements.push_back({ count, GL_FLOAT });
		m_stride += sizeof(GLfloat) * count;
	}

	inline const vector<Element> getElements() const { return m_elements; }
	size_t getStride() const;
private:
	size_t m_stride;
	vector<Element> m_elements;
};

