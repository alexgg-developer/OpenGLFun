#pragma once

using namespace std;

class IRenderable
{
public:
	IRenderable() {}
	virtual ~IRenderable() {}
	virtual void draw() const = 0;
private:
};

