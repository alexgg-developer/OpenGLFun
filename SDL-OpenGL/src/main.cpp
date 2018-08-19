#include <iostream>
#include <chrono>

/*#include "apps\TexturesApp.h"
#include "apps\TransformsApp.h"
#include "apps\DepthApp.h"
#include "apps\StencilApp.h"
#include "apps\OutlineStencilApp.h"*/
#include "apps\FrameBufferApp.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
auto t_start = std::chrono::high_resolution_clock::now();


int main(int, char**)
{	
	//TexturesApp tApp(SCREEN_WIDTH, SCREEN_HEIGHT);
	//TransformsApp tApp(SCREEN_WIDTH, SCREEN_HEIGHT);
	//DepthApp tApp(SCREEN_WIDTH, SCREEN_HEIGHT);
	//StencilApp tApp(SCREEN_WIDTH, SCREEN_HEIGHT);
	//OutlineStencilApp tApp(SCREEN_WIDTH, SCREEN_HEIGHT);
	FrameBufferApp tApp(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Start up SDL and create window
	if (!tApp.setup()) {
		printf("Failed to initialize!\n");
		return 1;
	}
	tApp.mainLoop();	
	tApp.close();

	return 0;	
}