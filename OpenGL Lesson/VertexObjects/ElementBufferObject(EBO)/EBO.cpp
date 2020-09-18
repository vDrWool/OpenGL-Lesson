#include "EBO.h"

OGL::ElementBufferObject::ElementBufferObject() : OGL::AbstVertObject() {}


void OGL::ElementBufferObject::use(GLuint howToDraw)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->_data), this->_data, howToDraw);
}

void OGL::ElementBufferObject::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ID);

	this->_bind = true;
}

void OGL::ElementBufferObject::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->_bind = false;
}