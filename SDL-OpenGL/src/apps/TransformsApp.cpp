#include "TransformsApp.h"
#include "base\DebugTools.h"


TransformsApp::TransformsApp(int width, int height) :
	IApp(width, height),
	m_isRotationActivated(false),
	m_currentSpeed(INITIAL_ROTATION_SPEED),
	m_currentDegrees(0.0f)
{
}


TransformsApp::~TransformsApp()
{
}

bool TransformsApp::initRenderer()
{
	unique_ptr<ShaderProgram> program = make_unique<ShaderProgram>();
	program->init();
	//Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/transform.vert");
	Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/flip_transform.vert");
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
	m_renderer.addUniform("transform");

	return success;
}

bool TransformsApp::init()
{
	m_transform = glm::mat4(1.0f);
	//eye, center, up
	m_view = glm::lookAt(
		glm::vec3(1.2f, 1.2f, 1.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / m_height, 1.0f, 10.0f);
	//m_transform = glm::scale(m_transform, glm::vec3(2, 2, 2));
	m_renderer.addUniform("view");
	m_renderer.addUniform("proj");
	/*m_renderer.activateProgram();
	//glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	m_renderer.setUniformValue("view", 1, GL_FALSE, m_view);
	m_renderer.setUniformValue("proj", 1, GL_FALSE, m_projection);
	m_renderer.deactivateProgram();*/

	return true;
}

bool TransformsApp::setup()
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
		}
	}

	return success;
}

void TransformsApp::update()
{
	IApp::update();
	float dt = static_cast<float>(m_msNow - m_msLast) / 1000.0f;
	if (m_isRotationActivated) {
		/*m_currentSpeed -= (INITIAL_ROTATION_SPEED * 0.3f * dt);
		m_currentSpeed = std::fmaxf(m_currentSpeed, INITIAL_ROTATION_SPEED * 0.1f);
		m_currentDegrees += m_currentSpeed;
		if (m_currentDegrees >= 360.0f) {
			m_currentDegrees = 0;
			m_isRotationActivated = false;
			m_currentSpeed = INITIAL_ROTATION_SPEED;
		}
		cout << "m_currentDegrees::" << m_currentDegrees << endl;
		cout << "m_currentSpeed::" << m_currentSpeed << endl;
		m_transform = glm::rotate(glm::mat4(1.0f), glm::radians(m_currentDegrees), glm::vec3(1.0f, 0.0f, 0.0f));*/
	}
	m_transform = glm::rotate(m_transform, glm::radians(m_currentDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	m_currentSpeed /= 1.0f + dt;
	m_currentDegrees += 5 * m_currentSpeed * dt;
}

void TransformsApp::render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//Bind program
	m_renderer.activateProgram();
	float elapsed = static_cast<float>(m_msElapsed) / 1000.0f;
	//m_transform = glm::rotate(m_transform, elapsed * 0.001f * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));


	m_renderer.setUniformValue("time", elapsed);
	m_renderer.setUniformValue("model", 1, GL_FALSE, m_transform);
	m_renderer.setUniformValue("view", 1, GL_FALSE, m_view);
	m_renderer.setUniformValue("proj", 1, GL_FALSE, m_projection);

	m_renderer.draw();

}

void TransformsApp::close()
{
	//Deallocate program
	m_renderer.clean();
	IApp::close();
}

void TransformsApp::handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		//gRenderQuad = !gRenderQuad;
	}
	else if (key == ' ') {
		m_isRotationActivated = true;
		m_currentSpeed = 180.0f;
	}
}

void TransformsApp::mainLoop()
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
