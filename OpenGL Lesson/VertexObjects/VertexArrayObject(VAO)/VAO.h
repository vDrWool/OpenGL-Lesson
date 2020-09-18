#pragma once
#include <iostream>

#include "glad/glad.h"

#include "../VertexBufferObject(VBO)/VBO.h"
#include "../ElementBufferObject(EBO)/EBO.h"

namespace OGL
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject(const VertexArrayObject&) = delete;
		VertexArrayObject(const VertexArrayObject&&) = delete;

		VertexArrayObject& operator = (const VertexArrayObject&) = delete;
	public:
		VertexArrayObject();

		bool isBinded() noexcept;

		void bind();
		void unbind();
		void init(GLfloat* vboData, GLfloat* eboIndexes = nullptr);
		void vertexAttib(GLuint index, GLuint size, GLsizei stride, const void *pointer);

	private:
		GLuint _ID{};
		VBO _VBO{};
		EBO _EBO{};

		bool _bind{};
	};

	using VAO = VertexArrayObject;
}