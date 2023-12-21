#include "Core/Application.h"

int main(void)
{
	OpenGL::Application* application = new OpenGL::Application(std::string("OpenGL Sandbox"), 1600, 900);
	application->Run();
	delete application;

	return 0;
}


