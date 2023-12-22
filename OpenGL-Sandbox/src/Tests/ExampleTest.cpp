#include "ExampleTest.h"

#include <Glad/glad.h>
#include <imgui/imgui.h>

namespace OpenGL {

	ExampleTest::ExampleTest()
	{
	}

	ExampleTest::~ExampleTest()
	{
	}

	void ExampleTest::OnUpdate(float dt)
	{
		glClearColor(0.5f, 0.3f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void ExampleTest::OnImGuiRender(float dt)
	{
		ImGui::Text("Bla bla car");
		static float a = 5.0f;
		ImGui::DragFloat("Numa", &a);
	}

}