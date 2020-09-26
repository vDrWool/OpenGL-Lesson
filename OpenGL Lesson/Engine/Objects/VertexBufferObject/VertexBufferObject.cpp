#include "VertexBufferObject.h"

OGL::VertexBufferObject::VertexBufferObject(const GLfloat* data, const GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &(this->_ID));
	glBindBuffer(GL_ARRAY_BUFFER, this->_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}



void OGL::VertexBufferObject::bind(const GLuint id)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void OGL::VertexBufferObject::unBindAll()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


const GLuint OGL::VertexBufferObject::getID() const noexcept
{
	return this->_ID;
}



OGL::VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &(this->_ID));
}
