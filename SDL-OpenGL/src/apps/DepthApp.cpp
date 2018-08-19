#include "DepthApp.h"
#include "base\DebugTools.h"


DepthApp::DepthApp(int width, int height) :
	IApp(width, height)
{
}


DepthApp::~DepthApp()
{
}

bool DepthApp::initRenderer()
{
	glEnable(GL_DEPTH_TEST);

	unique_ptr<ShaderProgram> program = make_unique<ShaderProgram>();
	program->init();
	Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/mvp_simple_texture.vert");
	if (!vertexShader.compile()) {
		return false;
	}
	program->addShader(vertexShader);
	Shader fragmentShader(Shader::Kind::FRAGMENT, "Resources/shaders/texture_flipped.frag");
	if (!fragmentShader.compile()) {
		return false;
	}
	program->addShader(fragmentShader);
	program->link();
	program->activate();

	bool success = m_renderer.init(std::move(program));
	m_renderer.addUniform("time");
	m_renderer.addUniform("transform");

	return success;
}

bool DepthApp::init()
{
	m_transform = glm::mat4(1.0f);
	//eye, center, up
	m_view = glm::lookAt(
		//glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(1.5f, 1.5f, 1.5f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / m_height, 0.01f, 100.0f);
	m_renderer.addUniform("view");
	m_renderer.addUniform("proj");

	return true;
}

bool DepthApp::initGeometry()
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
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};
	/*vector<float> vertices = {
		// X      Y     Z     R     G     B     U     V
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};*/

	/*vector<float> vertices = {
		// X      Y     Z     R     G     B     U     V
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};*/


	/*vector<float> vertices = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};*/
	
	/*vector<float> vertices = {
		// X      Y     Z     R     G     B     U     V
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		- 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};*/

	/*vector<float> vertices = {
		// X      Y     Z     R     G     B     U     V
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};*/


	vector<size_t> indexData = {
		0, 1, 2,
		2, 3, 0
	};

	//m_renderer.addGeometry(std::move(vertices));
	m_renderer.addGeometry(std::move(vertices), std::move(indexData));

	return true;
}

bool DepthApp::setup()
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
						if (!init()) {
							cout << "Unable to initialize app" << endl;
							success = false;
						}
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

void DepthApp::update()
{
	IApp::update();
	float dt = static_cast<float>(m_msNow - m_msLast) / 1000.0f;
}

void DepthApp::render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Bind program
	m_renderer.activateProgram();
	float elapsed = static_cast<float>(m_msElapsed) / 1000.0f;

	m_renderer.setUniformValue("time", elapsed);
	m_renderer.setUniformValue("model", 1, GL_FALSE, m_transform);
	m_renderer.setUniformValue("view", 1, GL_FALSE, m_view);
	m_renderer.setUniformValue("proj", 1, GL_FALSE, m_projection);

	m_renderer.drawArray();
	//m_renderer.draw();
	//m_renderer.draw3D();

}

void DepthApp::close()
{
	//Deallocate program
	m_renderer.clean();
	IApp::close();
}

void DepthApp::handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		//gRenderQuad = !gRenderQuad;
	}
	else if (key == ' ') {
	}
}

void DepthApp::mainLoop()
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
