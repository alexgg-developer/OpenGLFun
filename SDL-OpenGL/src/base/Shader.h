#pragma once
class Shader
{
public:
	Shader();
	~Shader();
	bool init(const KindOfShader kind);
	bool init(const KindOfShader kind, const std::string path);
	void logErrors();
private:
	enum KindOfShader { VERTEX, FRAGMENT, GEOMETRY };

	uint mProgramID;

	void initShaderSource(const std::string source);
	
};

