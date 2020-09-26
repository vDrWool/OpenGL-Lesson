#pragma once
#include "VertexBufferLayout.h"
#include "../VertexBufferObject/VertexBufferObject.h"

namespace OGL
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject();

		static void bind(const GLuint id);
		static void unBindAll();

		void addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& vbl);

		GLuint getID() const noexcept;

		~VertexArrayObject();
	private:
		GLuint _ID{};
	};

	using VAO = VertexArrayObject;
}

