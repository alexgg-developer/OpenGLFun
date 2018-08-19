#include "OutlineStencilApp.h"
#include "base\DebugTools.h"


OutlineStencilApp::OutlineStencilApp(int width, int height) :
	IApp(width, height),
	RED_COLOR(glm::vec3(1.0f, 0.0f, 0.0f)),
	BLUE_COLOR(glm::vec3(0.0f, 0.0f, 1.0f)),
	GREEN_COLOR(glm::vec3(0.0f, 1.0f, 0.0f))
{
}


OutlineStencilApp::~OutlineStencilApp()
{
}

bool OutlineStencilApp::initRenderer()
{
	glEnable(GL_DEPTH_TEST);

	unique_ptr<ShaderProgram> program = make_unique<ShaderProgram>();
	program->init();
	//Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/mvp_simple_texture_override.vert");
	Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/mvp_simple.vert");
	//Shader vertexShader(Shader::Kind::VERTEX, "Resources/shaders/simple.vert");
	if (!vertexShader.compile()) {
		return false;
	}
	program->addShader(vertexShader);
	//Shader fragmentShader(Shader::Kind::FRAGMENT, "Resources/shaders/texture_flipped.frag");
	Shader fragmentShader(Shader::Kind::FRAGMENT, "Resources/shaders/simple_color.frag");
	if (!fragmentShader.compile()) {
		return false;
	}
	program->addShader(fragmentShader);
	program->link();
	program->activate();


	bool success = m_renderer.init(std::move(program));

	m_renderer.addUniform("time");
	m_renderer.addUniform("transform");
	m_renderer.addUniform("override");
	m_renderer.addUniform("prueba");
	m_renderer.addUniform("view");
	m_renderer.addUniform("proj");

	m_renderer.deactivateProgram();

	return success;
}

bool OutlineStencilApp::init()
{
	m_transform = glm::mat4(1.0f);
	//eye (or position), center (or lookat), up
	m_view = glm::lookAt(
		/*glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(10.0f, 10.0f, -10.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)*/
		glm::vec3(4.0f, 4.0f, 4.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
		/*glm::vec3(2.5f, 2.5f, 2.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)*/
	);
	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / m_height, 0.01f, 100.0f);

	return true;
}

bool OutlineStencilApp::initGeometry()
{
	//m_renderer.addGeometry(std::move(vertices));
	m_renderer.addGeometry(m_cube.getVertices());

	return true;
}

bool OutlineStencilApp::setup()
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

void OutlineStencilApp::update()
{
	m_renderer.printShaderLogs();

	IApp::update();
	float dt = static_cast<float>(m_msNow - m_msLast) / 1000.0f;
}

void OutlineStencilApp::render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Bind program
	m_renderer.activateProgram();
	m_renderer.printShaderLogs();
	float elapsed = static_cast<float>(m_msElapsed) / 1000.0f;

	//m_renderer.setUniformValue("time", elapsed);
	m_renderer.setUniformValue("model", 1, GL_FALSE, m_transform);
	m_renderer.setUniformValue("view", 1, GL_FALSE, m_view);
	m_renderer.setUniformValue("proj", 1, GL_FALSE, m_projection);
	m_renderer.setUniformValue("prueba", glm::vec3(1.0f, 0, 1));
	//m_renderer.setUniformValue("prueba", RED_COLOR.r);

	//m_renderer.draw();
	//m_renderer.draw3D();
	//m_renderer.drawArrayWithStencil();
	//m_renderer.drawArray();

	drawOutlining();

	m_renderer.deactivateProgram();

}

void OutlineStencilApp::drawOutlining()
{
	// Render the mesh into the stencil buffer.

	glClearStencil(0);
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_ALWAYS, 1, -1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
	//m_renderer.setUniformValue("override", RED_COLOR);
	//m_renderer.setUniformValue("override", RED_COLOR.r, RED_COLOR.g, RED_COLOR.b);
	m_renderer.setUniformValue("override", glm::vec3(1.0f, 0, 1));
	drawArray();

	// Render the thick wireframe version.

	glStencilFunc(GL_NOTEQUAL, 1, -1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//m_renderer.setUniformValue("override", GREEN_COLOR);
	//m_renderer.setUniformValue("override", color.r, color.g, color.b);*/
	m_renderer.setUniformValue("override", glm::vec3(0.0f, 0, 0));
	drawArray();
}

void OutlineStencilApp::drawArray()
{
	//Enable vertex position
	GLuint positionLocation = m_renderer.getAttributeLocation("position");
	glEnableVertexAttribArray(positionLocation);
	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer.getVBO());
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	/*glEnableVertexAttribArray(m_attributeLocations["color"]);
	glVertexAttribPointer(m_attributeLocations["color"], 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(m_attributeLocations["inTexcoord"]);
	glVertexAttribPointer(m_attributeLocations["inTexcoord"], 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));*/
	//Set index data and render
	glDrawArrays(GL_TRIANGLES, 0, m_cube.getVertices().size() / 3);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(positionLocation);
	//glDisableVertexAttribArray(m_attributeLocations["color"]);
	//glDisableVertexAttribArray(m_attributeLocations["inTexcoord"]);
}

void OutlineStencilApp::close()
{
	//Deallocate program
	m_renderer.clean();
	IApp::close();
}

void OutlineStencilApp::handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		//gRenderQuad = !gRenderQuad;
	}
	else if (key == ' ') {
	}
}

void OutlineStencilApp::mainLoop()
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
