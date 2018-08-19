#include "IApp.h"



IApp::IApp(int width, int height): m_width(width), m_height(height)
{
}


IApp::~IApp()
{
}

void IApp::update()
{
	m_msElapsed = SDL_GetTicks();
	m_msLast = m_msNow;
	m_msNow = SDL_GetTicks();
}

void IApp::close()
{
	//Destroy window	
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

