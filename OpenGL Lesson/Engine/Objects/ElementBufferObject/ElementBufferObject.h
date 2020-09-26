#pragma once
#include "glad/glad.h"


namespace OGL
{
	class ElementBufferObject
	{
	public:
		ElementBufferObject(const GLuint* data, const GLuint size, GLenum usage);

		static void Bind(const GLuint id);
		static void Unbind();

		GLuint getID() const noexcept;
		GLuint getCount() const noexcept;

		~ElementBufferObject();
	private:
		GLuint _ID{};
		GLuint _count{};
	};

	using EBO = ElementBufferObject;
}