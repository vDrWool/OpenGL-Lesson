#pragma once
#include "glad/glad.h"

namespace OGL {
	class VertexBufferObject
	{
	public:
		VertexBufferObject(const GLfloat* data, const GLsizeiptr size, GLenum usage);

		static void bind(const GLuint id);
		static void unBindAll();

		const GLuint getID() const noexcept;

		~VertexBufferObject();
	private:
		GLuint _ID{};
	};
	
	using VBO = VertexBufferObject;
}

