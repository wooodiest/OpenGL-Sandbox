#pragma once

#include "Core/Test.h"

#include <glm/glm.hpp>
#include "Utils/Shader.h"

namespace OpenGL {

	class ExampleTest2 : public Test
	{
	public:
		ExampleTest2();
		virtual ~ExampleTest2();

		virtual void OnUpdate(float dt) override;
		virtual void OnImGuiRender(float dt) override;

	private:
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		unsigned int m_VertexArray;
		Shader* m_Shader;

	private:
		glm::vec4 m_Color{ 1.0f, 0.5f, 0.2f, 1.0f };
	};

}