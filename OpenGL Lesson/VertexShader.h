#pragma once
#include <iostream>
#include <string>

#include "glad/glad.h"
#include "Shader.h"

namespace OGL
{
	class VertexShader : public Shader
	{
	public:
		VertexShader() = delete;
		VertexShader(const VertexShader&) = delete;
		VertexShader(const VertexShader&&) = delete;

		VertexShader(std::string sourcePath);
	};
}