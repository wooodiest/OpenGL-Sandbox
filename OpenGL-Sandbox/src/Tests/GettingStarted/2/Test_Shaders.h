#pragma once

#include "Core/Test.h"

#include <glm/glm.hpp>
#include "Utils/Shader.h"

namespace OpenGL {

	class Test_Shaders : public Test
	{
	public:
		Test_Shaders();
		virtual ~Test_Shaders();

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