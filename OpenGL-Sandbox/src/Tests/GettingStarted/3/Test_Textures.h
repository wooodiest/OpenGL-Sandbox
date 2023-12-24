#pragma once

#include "Core/Test.h"
#include "Utils/Shader.h"

#include <glm/glm.hpp>

namespace OpenGL {

	class Test_Textures : public Test
	{
	public:
		Test_Textures();
		virtual ~Test_Textures();

		virtual void OnUpdate(float dt);
		virtual void OnImGuiRender(float dt);

	private:
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		unsigned int m_VertexArray;

		unsigned int m_Texture1;
		unsigned int m_Texture2;

		Shader* m_Shader;
		glm::vec4 m_Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	};

}