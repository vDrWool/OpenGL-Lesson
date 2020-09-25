#include "VertexBufferLayout.h"


GLuint OGL::VertexBufferElement::getSizeOfType(GLuint type)
{
	switch (type)
	{
		case GL_FLOAT:         return sizeof(GLfloat);
		case GL_UNSIGNED_INT:  return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
	}

	ASSERT(false);
	return 0;
}



OGL::VertexBufferLayout::VertexBufferLayout() : _stride{ 0 } {}


const std::vector<OGL::VertexBufferElement>& OGL::VertexBufferLayout::getElements() const
{
	return this->_elements;
}

GLuint OGL::VertexBufferLayout::getStride() const
{
	return this->_stride;
}