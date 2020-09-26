#include "ElementBufferObject.h"

OGL::ElementBufferObject::ElementBufferObject(const GLuint* data, const GLuint size, GLenum usage)
	: _count{ size }
{
	glGenBuffers(1, &(this->_ID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}


void OGL::ElementBufferObject::Bind(const GLuint id)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void OGL::ElementBufferObject::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint OGL::ElementBufferObject::getID() const noexcept
{
	return this->_ID;
}

GLuint OGL::ElementBufferObject::getCount() const noexcept
{
	return this->_count;
}


OGL::ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &(this->_ID));
}
