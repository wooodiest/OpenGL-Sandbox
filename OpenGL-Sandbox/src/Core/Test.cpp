#include "Test.h"

#include <Glad/glad.h>
#include <imgui/imgui.h>

namespace OpenGL {

	TestMenu::TestMenu(Test*& currentTestMenu)
		: m_CurrentTest(currentTestMenu)
	{
	}

	TestMenu::~TestMenu()
	{
	}

	void TestMenu::OnUpdate(float dt)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestMenu::OnImGuiRender(float dt)
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str(), ImVec2(ImGui::GetWindowSize().x, 0.0f)))
				m_CurrentTest = test.second();
		}
	}

}