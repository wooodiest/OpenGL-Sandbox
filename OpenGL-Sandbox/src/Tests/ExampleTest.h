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
	};

}