#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace OpenGL {

	class Application
	{
	public:
		Application(std::string& name, uint32_t width, uint32_t height);
		~Application();

		static Application& Get() { return *s_Instance; }
		GLFWwindow& GetWindow() { return *m_Window; }
		float GetDeltaTime() const { return m_DeltaTime; }

		void Init();
		void Run();
		void Shutdown();

	private:
		GLFWwindow* m_Window = nullptr;
		std::string m_Name;
		uint32_t m_WindowWidth, m_WindowHeight;

		float m_LastFrameTime = 0.0f;
		float m_DeltaTime = (1.0f / 60.0f);

	private:
		static Application* s_Instance;

	};

}