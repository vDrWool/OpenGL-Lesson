#pragma once
#include "glad/glad.h"


namespace OGL
{
	class ElementBufferObject
	{
	public:
		ElementBufferObject(const GLuint* data, const GLsizeiptr size, GLenum usage);

		static void bind(const GLuint id);
		static void unBindAll();

		GLuint getID() const noexcept;

		~ElementBufferObject();
	private:
		GLuint _ID{};
	};

	using EBO = ElementBufferObject;
}