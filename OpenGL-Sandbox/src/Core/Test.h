#pragma once

#include <vector>
#include <string>
#include <functional>

namespace OpenGL {

	class Test
	{
	public:
		Test() = default;
		virtual ~Test() = default;

		virtual void OnUpdate(float dt) {}
		virtual void OnImGuiRender(float dt) {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestMenu);
		virtual ~TestMenu();

		virtual void OnUpdate(float dt) override;
		virtual void OnImGuiRender(float dt) override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			m_Tests.emplace_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;

	};
}