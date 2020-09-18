#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"

namespace OGL{
	class Shader
	{
	public:
		Shader(std::string sourcePath, GLenum type);

		[[nodiscard]] const char* getShaderSource() const noexcept;
		[[nodiscard]] GLuint getID() const noexcept;

		virtual ~Shader() noexcept;
	protected:
		void privateCreateShader(GLenum type);
	protected:
		std::string _path{};
		const char* _shaderSource{};
		GLuint _ID{};
	};
}
