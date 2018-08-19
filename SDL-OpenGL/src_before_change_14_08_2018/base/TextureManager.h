#pragma once
#include <map>


#include "Texture.h"

using namespace std;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
private:
	map<string, Texture> m_textures;

};

