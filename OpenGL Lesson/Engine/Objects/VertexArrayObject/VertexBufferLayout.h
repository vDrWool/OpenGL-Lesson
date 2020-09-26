#pragma once
#include <vector>

#include "glad/glad.h"


namespace OGL
{
	struct VertexBufferElement
	{
		GLuint type{};
		GLuint count{};
		GLuint normolised{};

		static GLuint getSizeOfType(GLuint type);
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();

		template<typename T>
		void push(GLuint count)
		{
			static_assert(false);
		}
		template<>
		void push<GLfloat>(GLuint count)
		{
			this->_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			this->_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
		}
		template<>
		void push<GLuint>(GLuint count)
		{
			this->_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			this->_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
		}
		template<>
		void push<GLbyte>(GLuint count)
		{
			this->_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			this->_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
		}

		const std::vector<VertexBufferElement>& getElements() const;
		GLuint getStride() const;
	private:
		std::vector<VertexBufferElement> _elements{};
		GLuint _stride{};
	};

	using VBL = VertexBufferLayout;
}