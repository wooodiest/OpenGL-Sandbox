#pragma once

#include <string>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Test.h"

namespace OpenGL {

	class Application
	{
	public:
		Application(std::string& name, uint32_t width, uint32_t height);
		~Application();

		static Application& Get() { return *s_Instance; }
		GLFWwindow* GetWindow() { return m_Window; }
		float GetDeltaTime() const { return m_DeltaTime; }
		glm::vec2 GetViewPortSize() { return { m_WindowWidth, m_WindowHeight }; }
		void SetViewPortSize(const glm::vec2& v) { m_WindowWidth = v.x; m_WindowHeight = v.y; }

		void Init();
		void Run();
		void Shutdown();

	private:
		void BeginImGuiFrame();
		void EndImGuiFrame();

	private:
		GLFWwindow* m_Window = nullptr;
		std::string m_Name;
		uint32_t m_WindowWidth, m_WindowHeight;

		float m_LastFrameTime = 0.0f;
		float m_DeltaTime = (1.0f / 60.0f);

		Test* m_CurrentTest = nullptr;
		TestMenu* m_TestMenu = nullptr;

	private:
		static Application* s_Instance;

	};

}