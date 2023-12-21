#include "Application.h"

#include <iostream>
#include <Glad/glad.h>

namespace OpenGL {

	Application* Application::s_Instance = nullptr;

	Application::Application(std::string& name, uint32_t width, uint32_t height)
		: m_Name(name), m_WindowWidth(width), m_WindowHeight(height)
	{
		s_Instance = this;
		Init();
	}

	Application::~Application()
	{
	}

	void Application::Init()
	{
		if (!glfwInit())
			std::cout << "Cannot initialize glfw" << std::endl;

		m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_Name.c_str(), NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Cannot create window" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Cannot initialize glad" << std::endl;
			Shutdown();
		}

		glfwSwapInterval(1);
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			float time = (float)glfwGetTime();
			m_DeltaTime = time - m_LastFrameTime;
			m_DeltaTime = m_DeltaTime > (1.0f / 60.0f) ? (1.0f / 60.0f) : m_DeltaTime;
			m_LastFrameTime = time;

			glClearColor(0.5f, 0.3f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	void Application::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

}