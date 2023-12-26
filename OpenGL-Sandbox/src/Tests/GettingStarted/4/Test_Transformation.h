#pragma once

#include "Core/Test.h"
#include "Utils/Shader.h"

#include <glm/glm.hpp>

namespace OpenGL {

	class Test_Transformation : public Test
	{
	public:
		Test_Transformation();
		virtual ~Test_Transformation();

		virtual void OnUpdate(float dt);
		virtual void OnImGuiRender(float dt);

	private:
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		unsigned int m_VertexArray;
		unsigned int m_Texture;

		glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Scale{ 1.0f };
		float m_Rotation = 0.0f;

		Shader* m_Shader;
		glm::vec4 m_Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	};

}