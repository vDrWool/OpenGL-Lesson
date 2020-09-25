#include "VertexBufferObject.h"

OGL::VertexBufferObject::VertexBufferObject(const GLfloat* data, const GLsizeiptr size, GLenum usage)
{
	GLCall(glGenBuffers(1, &(this->_ID)));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}



void OGL::VertexBufferObject::bind(const GLuint id)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void OGL::VertexBufferObject::unBindAll()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


inline GLuint OGL::VertexBufferObject::getID() const noexcept
{
	return this->_ID;
}



OGL::VertexBufferObject::~VertexBufferObject()
{
	GLCall(glDeleteBuffers(1, &(this->_ID)));
}
