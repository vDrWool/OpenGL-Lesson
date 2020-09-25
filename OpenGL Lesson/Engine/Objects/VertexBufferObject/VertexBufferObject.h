#pragma once
#include "../../Utilities/OGL.h"


namespace OGL {
	class VertexBufferObject
	{
	public:
		VertexBufferObject(const VertexBufferObject&) = delete;
		VertexBufferObject(const VertexBufferObject&&) = delete;

		VertexBufferObject& operator = (const VertexBufferObject&) = delete;
	public:
		VertexBufferObject(const GLfloat* data, const GLsizeiptr size, GLenum usage);

		static void bind(const GLuint id);
		static void unBindAll();

		[[nodiscard]] inline GLuint getID() const noexcept;

		~VertexBufferObject();
	private:
		GLuint _ID{};
	};
	
	using VBO = VertexBufferObject;
}

