#include "Application.h"

#include <iostream>
#include <Glad/glad.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "Tests/GettingStarted/1/ExampleTest.h"
#include "Tests/GettingStarted/2/ExampleTest2.h"

namespace OpenGL {

	Application* Application::s_Instance = nullptr;
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	Application::Application(std::string& name, uint32_t width, uint32_t height)
		: m_Name(name), m_WindowWidth(width), m_WindowHeight(height)
	{
		s_Instance = this;
		Init();

		m_TestMenu = new TestMenu(m_CurrentTest);
		m_CurrentTest = m_TestMenu;

		m_TestMenu->RegisterTest<ExampleTest>("Example1");
		m_TestMenu->RegisterTest<ExampleTest2>("Example2");
	}

	Application::~Application()
	{
		Shutdown();
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
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSwapInterval(1);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			// Delta time calculation
			float time = (float)glfwGetTime();
			m_DeltaTime = time - m_LastFrameTime;
			m_DeltaTime = m_DeltaTime > (1.0f / 60.0f) ? (1.0f / 60.0f) : m_DeltaTime;
			m_LastFrameTime = time;

			// ImGui
			BeginImGuiFrame();

			if (m_CurrentTest)
			{
				// Tests menu
				ImGui::Begin("Tests");
				m_CurrentTest->OnUpdate(m_DeltaTime);
				if (m_CurrentTest != m_TestMenu && ImGui::Button("<--", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
				{
					delete m_CurrentTest;
					m_CurrentTest = m_TestMenu;
				}
				m_CurrentTest->OnImGuiRender(m_DeltaTime);
				ImGui::End();
			}

			EndImGuiFrame();

			//
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	void Application::Shutdown()
	{
		delete m_CurrentTest;
		if (m_CurrentTest != m_TestMenu)
			delete m_TestMenu;
		

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Application::BeginImGuiFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Application::EndImGuiFrame()
	{
		ImGuiIO& io = ImGui::GetIO();
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Application::Get().SetViewPortSize({ width, height });
	}

}