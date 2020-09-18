#include "VBO.h"

OGL::VertexBufferObject::VertexBufferObject() : OGL::AbstVertObject() {}


void OGL::VertexBufferObject::use(GLuint howToDraw)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_data), this->_data, howToDraw);
}

void OGL::VertexBufferObject::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_ID);

	this->_bind = true;
}

void OGL::VertexBufferObject::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->_bind = false;
}