#pragma once
#include <iostream>

#include "../AbstarctObject/AbstVertObject.h"

namespace OGL
{
	class VertexBufferObject : public AbstVertObject
	{
	public:
		VertexBufferObject(const VertexBufferObject&) = delete;
		VertexBufferObject(const VertexBufferObject&&) = delete;

		VertexBufferObject& operator = (const VertexBufferObject&) = delete;
	public:
		VertexBufferObject();

		void use(GLuint howToDraw) override;
		void bind() override;
		void unbind() override;
	};

	using VBO = VertexBufferObject;
}