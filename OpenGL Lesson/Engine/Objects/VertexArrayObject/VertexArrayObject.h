#pragma once
#include "../../Utilities/OGL.h"

#include "VertexBufferLayout.h"
#include "../VertexBufferObject/VertexBufferObject.h"

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

		static void bind(const GLuint id);
		static void unBindAll();

		void addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& vbl);

		[[nodiscard]] inline GLuint getID() const noexcept;

		~VertexArrayObject();
	private:
		GLuint _ID{};
	};

	using VAO = VertexArrayObject;
}

