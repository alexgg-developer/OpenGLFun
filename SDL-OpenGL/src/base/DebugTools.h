#pragma once
#include <iostream>
#include <string>

using namespace std;

static class DebugTools
{
public:
	static void logSDLError(std::ostream &os, const std::string &msg);
};

