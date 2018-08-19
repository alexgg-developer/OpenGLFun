#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

/**
* Pre:
*	program: the program has been inited, linked and activated beforehand
*/
bool Renderer::init()
{
	bool success = true;

	

	return success;
}

void Renderer::draw(const IRenderable& renderable) const
{
	renderable.draw();
}