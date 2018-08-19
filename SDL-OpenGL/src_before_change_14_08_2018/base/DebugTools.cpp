#include "DebugTools.h"

void DebugTools::logSDLError(std::ostream & os, const std::string & msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}
