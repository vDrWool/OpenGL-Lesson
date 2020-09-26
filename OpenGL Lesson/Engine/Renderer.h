#pragma once
#include "Objects/VertexArrayObject/VertexArrayObject.h"
#include "Objects/ElementBufferObject/ElementBufferObject.h"
#include "Shaders/ShaderProgram/ShaderProgram.h"

namespace OGL
{
	class Renderer
	{
	public:
		static void Draw(const VertexArrayObject& vao, const ElementBufferObject& ebo, const ShaderProgram& sp);
	};
}