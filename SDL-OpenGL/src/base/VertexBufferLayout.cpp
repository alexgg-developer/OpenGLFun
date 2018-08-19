#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(): m_stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

/*inline const vector<Element> VertexBufferLayout::getElements() const
{
	return m_elements;
}*/

size_t VertexBufferLayout::getStride() const
{
	return m_stride;
}

