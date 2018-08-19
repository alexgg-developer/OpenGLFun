#include "TexturesApp.h"
#include "base\DebugTools.h"


TexturesApp::TexturesApp(int width, int height) : IApp(width, height)
{
}


TexturesApp::~TexturesApp()
{
}

bool TexturesApp::initGeometry()
{
	vector<float> vertices = {
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f/*,

														 //floor
														 - 1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
														 1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
														 1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
														 1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
														 -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
														 -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f*/
	};

	vector<size_t> indexData = {
		0, 1, 2,
		2, 3, 0
	};

	//m_renderer.addGeometry(std::move(vertices));
	m_renderer.addGeometry(std::move(vertices), std::move(indexData));

	return true;
}

bool TexturesApp::initRenderer()
{
	unique_ptr<ShaderProgram> program = make_unique<ShaderProgram>();
	program->init();
	Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/texture.vert");
	if (!vertexShader.compile()) {
		return false;
	}
	program->addShader(vertexShader);
	//Shader fragmentShader(Shader::Kind::FRAGMENT, "Resources/shaders/animated_blending.frag");
	Shader fragmentShader(Shader::Kind::FRAGMENT, "Resources/shaders/texture_reflection.frag");
	if (!fragmentShader.compile()) {
		return false;
	}
	program->addShader(fragmentShader);
	program->link();
	program->activate();

	bool success = m_renderer.init(std::move(program));
	m_renderer.addUniform("time");

	m_renderer.activateProgram();
	m_renderer.addAttribute("inTexcoord");
	Texture t0(GL_RGB, false, 0);
	t0.load("Resources/imgs/nehe.png");
	m_renderer.addUniform("textKitten");
	//glUniform1i(m_program->getUniformLocation("texKitten"), t0.getLocation());
	m_renderer.setUniformValue("textKitten", t0.getLocation());

	Texture t1(GL_RGB, false, 1);
	t1.load("Resources/imgs/strawberry.jpg");
	m_renderer.addUniform("texPuppy");
	//glUniform1i(m_program->getUniformLocation("texPuppy"), t1.getLocation());
	m_renderer.setUniformValue("texPuppy", t1.getLocation());
	m_renderer.deactivateProgram();

	return success;
}
bool TexturesApp::setup()
{
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		DebugTools::logSDLError(cout, "SDL_INIT");
		success = false;
	}
	else {
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		//Create window
		m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (m_window == nullptr) {
			DebugTools::logSDLError(std::cout, "CreateWindow");
			success = false;
		}
		else {
			//Create context
			m_context = SDL_GL_CreateContext(m_window);
			if (m_context == NULL) {
				DebugTools::logSDLError(std::cout, "CreateContext");
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
				if (SDL_GL_SetSwapInterval(1) < 0) {
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}
				//Initialize OpenGL
				if (initGeometry()) {
					if (!initRenderer()) {
						printf("Unable to initialize OpenGL!\n");
						success = false;
					}
					else {
						/*if (!init()) {
							cout << "Unable to initialize app" << endl;
							success = false;
						}*/
					}
				}
				else {
					cout << "Unable to initialize app" << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

void TexturesApp::update()
{
	IApp::update();
}

void TexturesApp::render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//Bind program
	m_renderer.activateProgram();
	float elapsed = static_cast<float>(m_msElapsed) / 1000.0f;
	cout << "m_elapsed::" << elapsed << endl;
	m_renderer.setUniformValue("time", elapsed);
	m_renderer.drawArray();
}

void TexturesApp::close()
{
	//Deallocate program
	m_renderer.clean();
	IApp::close();
}

void TexturesApp::handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		//gRenderQuad = !gRenderQuad;
	}
}

void TexturesApp::mainLoop()
{
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
		//update logic
		update();
		//Render quad
		render();
		//Update screen
		SDL_GL_SwapWindow(m_window);
	}
}
