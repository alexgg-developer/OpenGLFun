#include "FrameBufferApp.h"
#include "base\DebugTools.h"


FrameBufferApp::FrameBufferApp(int width, int height) :
	IApp(width, height),
	m_frameBufferObject(width, height)
{
}


FrameBufferApp::~FrameBufferApp()
{
}

bool FrameBufferApp::initRenderer()
{
	bool success = true;

	glEnable(GL_DEPTH_TEST);

	m_program = make_shared<ShaderProgram>();
	m_program->init();
	Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/mvp_simple_texture_override.vert");
	if (!vertexShader.compile()) {
		success = false;
	}
	m_program->addShader(vertexShader);
	Shader fragmentShader(Shader::Kind::FRAGMENT, "Resources/shaders/texture_flipped.frag");
	if (!fragmentShader.compile()) {
		success = false;
	}
	m_program->addShader(fragmentShader);
	m_program->link();
	m_program->activate();
	m_program->addUniform("time");
	m_program->addUniform("transform");

	m_program->addAttribute("position");
	m_program->addAttribute("color");
	m_program->addAttribute("inTexcoord");
	Texture t0(GL_RGB, false, 0);
	t0.load("Resources/imgs/nehe.png");
	m_textures.push_back(t0);
	m_program->addUniform("textKitten");
	m_program->setUniformValue("textKitten", t0.getLocation());

	Texture t1(GL_RGB, false, 1);
	t1.load("Resources/imgs/strawberry.jpg");
	m_textures.push_back(t1);
	m_program->addUniform("texPuppy");
	m_program->setUniformValue("texPuppy", t1.getLocation());
	m_program->deactivate();

	m_frameBufferObject.init();

	return success;
}

bool FrameBufferApp::init()
{
	m_transform = glm::mat4(1.0f);
	//eye, center, up
	m_view = glm::lookAt(
		//glm::vec3(0.0f, 0.0f, 2.0f),
		//glm::vec3(1.5f, 1.5f, 1.5f),
		glm::vec3(2.5f, 2.5f, 2.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / m_height, 0.01f, 100.0f);
	m_program->addUniform("view");
	m_program->addUniform("proj");
	m_program->addUniform("overrideColor");

	return true;
}

bool FrameBufferApp::initGeometry()
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
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		//floor
		- 1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	
	m_mesh = make_unique<Mesh>(false);
	m_mesh->addVertices(vertices);
	m_mesh->init();
	VertexBufferLayout vertexBufferLayout;
	vertexBufferLayout.add<float>(3);
	vertexBufferLayout.add<float>(3);
	vertexBufferLayout.add<float>(2);
	m_mesh->setVertexBufferLayout(std::move(vertexBufferLayout));

	return true;
}

bool FrameBufferApp::setup()
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

void FrameBufferApp::update()
{
	IApp::update();
	float dt = static_cast<float>(m_msNow - m_msLast) / 1000.0f;
}

void FrameBufferApp::render()
{
	if (!m_frameBufferObject.isReady()) return;
	m_frameBufferObject.activate();
	//Clear color buffer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.0f, 0.4f, 1.0f, 1.0f);
	//Bind program
	m_program->activate();
	float elapsed = static_cast<float>(m_msElapsed) / 1000.0f;

	m_program->setUniformValue("time", elapsed);
	m_program->setUniformValue("model", 1, GL_FALSE, m_transform);
	m_program->setUniformValue("view", 1, GL_FALSE, m_view);
	m_program->setUniformValue("proj", 1, GL_FALSE, m_projection);
	m_program->setUniformValue("overrideColor", glm::vec3(1.0f, 1.0f, 1.0f));

	draw();

	float pixels[3];
	glReadPixels(0, 0, 1, 1, GL_RGB, GL_FLOAT, &pixels);
	cout << "pixels 1::" << std::to_string(pixels[0]) << endl;
	cout << "pixels 2::" << std::to_string(pixels[1]) << endl;
	cout << "pixels 3::" << std::to_string(pixels[2]) << endl;
	m_frameBufferObject.deactivate();

}

void FrameBufferApp::draw()
{
	
	//Enable vertex position
	m_mesh->draw();

	/*glEnable(GL_STENCIL_TEST);
	// Draw floor
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 36, 6);

	// Draw cube reflection
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(
		glm::translate(model, glm::vec3(0, 0, -1)),
		glm::vec3(1, 1, -1)
	);

	m_renderer.setUniformValue("model", 1, GL_FALSE, model);

	m_renderer.setUniformValue("overrideColor", glm::vec3(0.3f, 0.3f, 0.3f));
	//glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

	glDisable(GL_STENCIL_TEST);


	glDisableVertexAttribArray(m_renderer.getAttributeLocation("position"));
	glDisableVertexAttribArray(m_renderer.getAttributeLocation("color"));
	glDisableVertexAttribArray(m_renderer.getAttributeLocation("inTexcoord"));
	//Unbind program
	m_renderer.deactivateProgram();*/
}

void FrameBufferApp::close()
{
	//Deallocate program
	//m_program->clean();
	IApp::close();
}

void FrameBufferApp::handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		//gRenderQuad = !gRenderQuad;
	}
	else if (key == ' ') {
	}
}

void FrameBufferApp::mainLoop()
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
