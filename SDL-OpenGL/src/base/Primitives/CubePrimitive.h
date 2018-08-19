#pragma once

#include <vector>

using namespace std;

class CubePrimitive
{
public:
	CubePrimitive();
	~CubePrimitive();

	vector<float>& getVertices();
private:
	vector<float> m_vertices;
	vector<float> m_uvs;
	vector<float> m_colors;
};

