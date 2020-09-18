#pragma once
#include <iostream>

#include "../AbstarctObject/AbstVertObject.h"

namespace OGL
{
	class ElementBufferObject : public AbstVertObject
	{
	public:
		ElementBufferObject(const ElementBufferObject&) = delete;
		ElementBufferObject(const ElementBufferObject&&) = delete;

		ElementBufferObject& operator = (const ElementBufferObject&) = delete;
	public:
		ElementBufferObject();

		void use(GLuint howToDraw) override;
		void bind() override;
		void unbind() override;
	};

	using EBO = ElementBufferObject;
}