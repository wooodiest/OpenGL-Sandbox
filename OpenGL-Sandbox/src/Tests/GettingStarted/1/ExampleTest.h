#pragma once

#include "Core/Test.h"

#include <glm/glm.hpp>

namespace OpenGL {

	class ExampleTest : public Test
	{
	public:
		ExampleTest();
		virtual ~ExampleTest();

		virtual void OnUpdate(float dt) override;
		virtual void OnImGuiRender(float dt) override;

	private:
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		unsigned int m_VertexArray;

		unsigned int m_Shader;
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;

	private:
		glm::vec4 m_Color{ 1.0f, 0.5f, 0.2f, 1.0f };
	};

}