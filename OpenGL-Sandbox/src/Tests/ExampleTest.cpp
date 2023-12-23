#include "ExampleTest.h"

#include <Glad/glad.h>
#include <imgui/imgui.h>

#include <string>
#include <iostream>

namespace OpenGL {

	ExampleTest::ExampleTest()
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

		// Create shaders
		std::string vertexShader = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Position;
			
			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentShader = R"(
			#version 330 core
			layout (location = 0) out vec4 color;
			
			void main()
			{
				color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			}
		)";
		const char* vertexShader_CStr = vertexShader.c_str();
		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_VertexShader, 1, &vertexShader_CStr, NULL);
		glCompileShader(m_VertexShader);
		{ // Check shader compile
			int success;
			char infoLog[512];
			glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(m_VertexShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
			}
		}
		const char* fragmentShader_CStr = fragmentShader.c_str();
		m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_FragmentShader, 1, &fragmentShader_CStr, NULL);
		glCompileShader(m_FragmentShader);
		{ // Check shader compile
			int success;
			char infoLog[512];
			glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(m_FragmentShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
			}
		}
		// Create shader program
		m_Shader = glCreateProgram();
		glAttachShader(m_Shader, m_VertexShader);
		glAttachShader(m_Shader, m_FragmentShader);
		glLinkProgram(m_Shader);
		{ // Check linking
			int success;
			char infoLog[512];
			glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(m_Shader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::LINKING FAILED\n" << infoLog << std::endl;
			}
		}
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);

#if 0
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
	}

	ExampleTest::~ExampleTest()
	{
	}

	void ExampleTest::OnUpdate(float dt)
	{
		glClearColor(0.5f, 0.3f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_Shader);
		glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void ExampleTest::OnImGuiRender(float dt)
	{
	}

}