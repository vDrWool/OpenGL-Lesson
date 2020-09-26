#pragma once
#include "VertexBufferLayout.h"
#include "../VertexBufferObject/VertexBufferObject.h"

namespace OGL
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject();

		static void Bind(const GLuint id);
		static void Unbind();

		void addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& vbl);

		GLuint getID() const noexcept;

		~VertexArrayObject();
	private:
		GLuint _ID{};
	};

	using VAO = VertexArrayObject;
}

