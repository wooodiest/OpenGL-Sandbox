#pragma once

#include "Core/Test.h"

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
	};

}