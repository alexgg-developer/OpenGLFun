#include "IApp.h"



IApp::IApp()
{
}


IApp::~IApp()
{
}

bool IApp::initGL()
{
	//Success flag
	bool success = true;
	//Generate program
	gProgramID = glCreateProgram();
	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	string strVertexSource = readShader("Resources/shaders/texture.vert");
	const char* vertexSource = strVertexSource.c_str();
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE) {
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		checkErrorsShader(vertexShader);
		success = false;
	}
	else {
		//Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);
		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		string strFragmentSource = readShader("Resources/shaders/blend.frag");
		const char* fragmentSource = strFragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		//Compile fragment source
		glCompileShader(fragmentShader);
		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE) {
			printf("Unable to compile fragment shader %d!\n", fragmentShader);
			checkErrorsShader(fragmentShader);
			success = false;
		}
		else {
			//Attach fragment shader to program
			glAttachShader(gProgramID, fragmentShader);
			//Link program
			glLinkProgram(gProgramID);
			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE) {
				printf("Error linking program %d!\n", gProgramID);
				printProgramLog(gProgramID);
				success = false;
			}
			else {
				glUseProgram(gProgramID); //importante!
										  //Get vertex attribute location
										  //loadTextures();

				glActiveTexture(GL_TEXTURE0);
				loadTexture("Resources/imgs/nehe.png", GL_RGB, gTexture0);
				glUniform1i(glGetUniformLocation(gProgramID, "texKitten"), 0);
				glActiveTexture(GL_TEXTURE1);
				loadTexture("Resources/imgs/strawberry.jpg", GL_RGB, gTexture1);
				glUniform1i(glGetUniformLocation(gProgramID, "texPuppy"), 1);

				glBindFragDataLocation(gProgramID, 0, "outColor");
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "position");
				gColorAttribLocation = glGetAttribLocation(gProgramID, "color");
				gTextureAttribLocation = glGetAttribLocation(gProgramID, "inTexcoord");

				if (gVertexPos2DLocation != -1) {
					//Initialize clear color
					glClearColor(0.f, 1.f, 1.f, 1.f);
					//VBO data
					float vertices[] = {
						-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
						0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
						0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
						-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
					};
					/*GLfloat vertices[] =
					{
					-0.5f, -0.5f,
					0.5f, -0.5f,
					0.5f,  0.5f,
					-0.5f,  0.5f
					};*/
					//IBO data
					GLuint indexData[] = {
						0, 1, 2,
						2, 3, 0
					};
					glGenVertexArrays(1, &gVAO);
					glBindVertexArray(gVAO);
					//Create VBO
					glGenBuffers(1, &gVBO);
					glBindBuffer(GL_ARRAY_BUFFER, gVBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
					//Create IBO
					glGenBuffers(1, &gIBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

					glUseProgram(0);

				}
			}
		}
	}

	return success;
}
