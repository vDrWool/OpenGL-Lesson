#include "ElementBufferObject.h"

OGL::ElementBufferObject::ElementBufferObject(const GLuint* data, const GLsizeiptr size, GLenum usage)
{
	GLCall(glGenBuffers(1, &(this->_ID)));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}

void OGL::ElementBufferObject::bind(const GLuint id)
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void OGL::ElementBufferObject::unBindAll()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

inline GLuint OGL::ElementBufferObject::getID() const noexcept
{
	return this->_ID;
}

OGL::ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &(this->_ID));
}
