#pragma once
#include <iostream>

#include "glad/glad.h"

namespace OGL
{
	class AbstVertObject
	{
	public:
		AbstVertObject(const AbstVertObject&) = delete;
		AbstVertObject(const AbstVertObject&&) = delete;

		AbstVertObject& operator = (const AbstVertObject&) = delete;
	public:
		AbstVertObject();

		virtual void use(GLenum howToDraw) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;

		bool isBinded() noexcept;

		void setData(GLfloat *&data) noexcept;
		[[nodiscard]] virtual GLuint getId() noexcept;

		virtual ~AbstVertObject();
	protected:
		GLuint _ID{};
		GLfloat* _data{};

		bool _bind{};
	};
}