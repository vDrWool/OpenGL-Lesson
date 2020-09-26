#pragma once
#include <string>
#include <iostream>
#include <unordered_map>

#include "../Shader/Shader.h"

namespace OGL
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;

		ShaderProgram(const VertexShader&&,
			          const FragmentShader&&,
			          const GeometryShader&& = GeometryShader()) noexcept;
		 
		static void Bind(const GLuint id);
		static void Unbind();

		const GLuint getID() const noexcept;

		void setUniform1b(const std::string& name, bool value);
		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniform4f(const std::string&, float u1, float u2, float u3, float u4);

		~ShaderProgram() noexcept;
	private:
		GLint privateGetUniformLocation(const std::string& name);
	private:
		GLuint _ID{};
		std::unordered_map<std::string, GLint> _uniformCache{};
	};
}

