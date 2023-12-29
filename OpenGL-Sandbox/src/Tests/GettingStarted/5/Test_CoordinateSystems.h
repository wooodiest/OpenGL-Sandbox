#pragma once

#include "Core/Test.h"
#include "Utils/Shader.h"
#include <glm/glm.hpp>

namespace OpenGL {

	class Test_CoordinateSystems : public Test
	{
	public:
		Test_CoordinateSystems();
		virtual ~Test_CoordinateSystems();

		virtual void OnUpdate(float dt);
		virtual void OnImGuiRender(float dt);

	private:
		void ProcessInput(float dt);

		unsigned int m_VertexBuffer;
		unsigned int m_VertexArray;
		unsigned int m_Texture;

		Shader* m_Shader;

		glm::vec4 m_Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		glm::mat4 m_Proj{ 1.0f };
		glm::mat4 m_View{ 1.0f };
		glm::mat4 m_Model{ 1.0f };

		glm::vec3 m_CamerPosition{ 0.0f, 0.0f, 3.0f };
		glm::vec3 m_CameraFront{ 0.0f, 0.0f, -1.0f };
		glm::vec3 m_CameraUp{ 0.0f, 1.0f, 0.0f };

	};

}