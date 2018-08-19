#pragma once

#include "ShaderProgram.h"
#include "Texture.h"
#include "IRenderable.h"

#include <vector>
#include <map>
#include <memory>

#include <glew.h>
#include <glm/glm.hpp>

using namespace std;

class Renderer
{
public:
	Renderer();
	~Renderer(); 	
	void draw(const IRenderable& renderable) const;
	bool init();
private:
};

