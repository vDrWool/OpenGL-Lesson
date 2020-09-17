#pragma once
#include <iostream>
#include <string>

#include "glad/glad.h"
#include "../AbstractShader/Shader.h"

namespace OGL
{
	class FragmentShader : public Shader
	{
	public:
		FragmentShader() = delete;
		FragmentShader(const FragmentShader&) = delete;
		FragmentShader(const FragmentShader&&) = delete;

		FragmentShader(std::string sourcePath);
	};
}

