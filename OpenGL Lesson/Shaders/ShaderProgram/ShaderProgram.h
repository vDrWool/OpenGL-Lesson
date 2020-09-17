#pragma once
#include <string>
#include <iostream>

#include "glad/glad.h"

#include "../VertexShader/VertexShader.h"
#include "../FragmentShader/FragmentShader.h"

namespace OGL
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;

		ShaderProgram(const VertexShader&, const FragmentShader&) noexcept;
		 
		void use() const noexcept;

		// Uniform functions.
		void setBool(const std::string&, bool) const;
		void setInt(const std::string&, int) const;
		void setFloat(const std::string&, float) const;

		~ShaderProgram() noexcept;
	private:
		GLuint _ID{};
	};
}

