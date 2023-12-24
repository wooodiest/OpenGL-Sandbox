#include "Test_Shaders.h"

#include "Core/Application.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

namespace OpenGL {

	Test_Shaders::Test_Shaders()
	{
		// Create vertex array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		// Create buffers
		float verticies[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		unsigned int indices[] {
			0, 1, 2,
			0, 2, 3
		};

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		m_Shader = new Shader("src/Tests/GettingStarted/2/shader.vertex.glsl", "src/Tests/GettingStarted/2/shader.fragment.glsl");
	}

	Test_Shaders::~Test_Shaders()
	{
		delete m_Shader;

		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteBuffers(1, &m_IndexBuffer);
		glDeleteVertexArrays(1, &m_VertexArray);
	}

	void Test_Shaders::OnUpdate(float dt)
	{
		if (glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		// Rendering
		glClearColor(0.5f, 0.3f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader->Bind();
		m_Shader->SetFloat4("u_Color", m_Color);

		glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Test_Shaders::OnImGuiRender(float dt)
	{
		ImGui::ColorPicker4("Color", glm::value_ptr(m_Color));
	}

}