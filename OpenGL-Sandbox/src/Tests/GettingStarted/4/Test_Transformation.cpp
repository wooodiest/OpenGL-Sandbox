#include "Test_Transformation.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include "Core/Application.h"

namespace OpenGL {

	Test_Transformation::Test_Transformation()
	{
		m_Shader = new Shader("src/Tests/GettingStarted/4/shader.vertex.glsl", "src/Tests/GettingStarted/4/shader.fragment.glsl");

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float verticies[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.5f, 1.0f
		};
		unsigned int indices[] = {
			0, 1, 2
		};

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		{
			glGenTextures(1, &m_Texture);
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			int width, height, channels;
			unsigned char* data = stbi_load("src/Tests/GettingStarted/4/wall.jpg", &width, &height, &channels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}

		m_Shader->Bind();
		m_Shader->SetInt("u_Texture", 0);
	}
	Test_Transformation::~Test_Transformation()
	{
		delete m_Shader;

		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteBuffers(1, &m_IndexBuffer);
		glDeleteVertexArrays(1, &m_VertexArray);
	}
	void Test_Transformation::OnUpdate(float dt)
	{
		if (glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		glClearColor(0.5f, 0.3f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader->Bind();
		m_Shader->SetFloat4("u_Color", m_Color);

		glm::mat4 transform{ 1.0f };
		transform = glm::translate(transform, m_Translation);
		transform = glm::rotate(transform, glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f });
		transform = glm::scale(transform, m_Scale);
		m_Shader->SetMat4("u_Transform", transform);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		glUseProgram(0);
	}
	void Test_Transformation::OnImGuiRender(float dt)
	{
		ImGui::ColorPicker4("Color", glm::value_ptr(m_Color));
		ImGui::DragFloat2("Transform", glm::value_ptr(m_Translation), 0.05f);
		ImGui::DragFloat2("Scale", glm::value_ptr(m_Scale), 0.05f);
		ImGui::DragFloat("Rotation", &m_Rotation, 5.0f);
	}


}
