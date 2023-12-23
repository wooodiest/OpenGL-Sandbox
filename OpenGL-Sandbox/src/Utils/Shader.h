#pragma once

#include <string>
#include <glm/glm.hpp>

namespace OpenGL {

	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind();

		void SetFloat4(const std::string& name, const glm::vec4& v);

	private:
		int m_RendererID;
	};

}