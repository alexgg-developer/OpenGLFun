#define GLEW_STATIC
#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void logSDLError(std::ostream &os, const std::string &msg);
void checkErrorsShader(GLuint shader);
string  readShader(std::string path);
void printProgramLog(GLuint program);
bool initGL();
void handleKeys(unsigned char key, int x, int y);
bool init();
void render();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;
GLuint gVAO = 0;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void checkErrorsShader(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	int infoLogLength = 0;
	int maxLength = infoLogLength;
	//Get info string length
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
	char* infoLog = new char[maxLength];
	glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
	std::cout << "--- Shader compile output ---" << std::endl;
	std::cout << infoLog << std::endl;
	std::cout << "--- --- ---" << std::endl;
	delete[] infoLog;
}


string readShader(std::string path)
{
	std::ostringstream sstream;
	//std::ifstream fs("Resources/shaders/simple.vert");
	ifstream fs(path);
	sstream << fs.rdbuf();
	return std::string(sstream.str());
}

void printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program)) {
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		//Allocate string
		char* infoLog = new char[maxLength];
		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			//Print Log
			printf("%s\n", infoLog);
		}
		//Deallocate string
		delete[] infoLog;
	}
	else {
		printf("Name %d is not a program\n", program);
	}
}

bool initGL()
{
	//Success flag
	bool success = true;
	//Generate program
	gProgramID = glCreateProgram();
	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	string strVertexSource = readShader("Resources/shaders/simple.vert");
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
	else
	{
		//Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);
		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		string strFragmentSource = readShader("Resources/shaders/simple.frag");
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
				//Get vertex attribute location
				glBindFragDataLocation(gProgramID, 0, "outColor");
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "position");
				if (gVertexPos2DLocation != -1) {
					//Initialize clear color
					glClearColor(1.f, 0.f, 0.f, 1.f);
					//VBO data
					/*float vertices[] = {
					0.0f,  0.5f, // Vertex 1 (X, Y)
					0.5f, -0.5f, // Vertex 2 (X, Y)
					-0.5f, -0.5f  // Vertex 3 (X, Y)
					};*/
					GLfloat vertices[] =
					{
						-0.5f, -0.5f,
						0.5f, -0.5f,
						0.5f,  0.5f,
						-0.5f,  0.5f
					};
					//IBO data
					GLuint indexData[] = { 0, 1, 2, 3 };					
					glGenVertexArrays(1, &gVAO);
					glBindVertexArray(gVAO);
					//Create VBO
					glGenBuffers(1, &gVBO);
					glBindBuffer(GL_ARRAY_BUFFER, gVBO);
					glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
					//Create IBO
					glGenBuffers(1, &gIBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
				}
			}
		}
	}

	return success;
}

void handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		//gRenderQuad = !gRenderQuad;
	}
}

bool init()
{
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		logSDLError(cout, "SDL_INIT");
		success = false;
	}
	else {
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == nullptr) {
			logSDLError(std::cout, "CreateWindow");
			success = false;
		}
		else {
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL) {
				logSDLError(std::cout, "CreateContext");
				success = false;
			}
			else {
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK) {
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if (!initGL()) {
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//Bind program
	glUseProgram(gProgramID);
	//Enable vertex position
	glEnableVertexAttribArray(gVertexPos2DLocation);
	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	//Disable vertex position
	glDisableVertexAttribArray(gVertexPos2DLocation);
	//Unbind program
	glUseProgram(NULL);
}

void close()
{
	//Deallocate program
	glDeleteProgram(gProgramID);
	glDeleteBuffers(1, &gVBO);
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

int main(int, char**)
{
	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
		return 1;
	}

	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	//Enable text input
	//SDL_StartTextInput();

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			//Handle keypress with current mouse position
			else if (e.type == SDL_TEXTINPUT) {
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				handleKeys(e.text.text[0], x, y);
			}
		}

		//Render quad
		render();

		//Update screen
		SDL_GL_SwapWindow(gWindow);
	}
	close();

	/*SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
	SDL_DestroyWindow(win);
	logSDLError(std::cout, "CreateRenderer");
	SDL_Quit();
	return 1;
	}*/


	// Create Vertex Array Object
	//GLuint vao;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	/*std::string imagePath = "Resources/example.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	logSDLError(std::cout, "SDL_LoadBMP");
	SDL_Quit();
	return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	logSDLError(std::cout, "SDL_CreateTextureFromSurface");
	SDL_Quit();
	return 1;
	}*/

	/*SDL_Event windowEvent;
	while (true)
	{
	if (SDL_PollEvent(&windowEvent))
	{
	if (windowEvent.type == SDL_QUIT) break;
	if (windowEvent.type == SDL_KEYUP &&
	windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
	}
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SDL_GL_SwapWindow(win);
	}
	//SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_GL_DeleteContext(context);
	SDL_Quit();


	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	return 0;*/
}