#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"

namespace OGL{
	template<GLenum type>
	class Shader
	{
	public:
		Shader();
		Shader(std::string sourcePath);

		[[nodiscard]] const char* getShaderSource() const noexcept;
		[[nodiscard]] GLuint getID() const noexcept;

		virtual ~Shader() noexcept;
	protected:
		void privateCreateShader();
	protected:
		const char* _path{};
		const char* _shaderSource{};
		GLuint _ID{};
	};

	using VertexShader   = Shader<GL_VERTEX_SHADER>;
	using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
	using GeometryShader = Shader<GL_GEOMETRY_SHADER>;
}