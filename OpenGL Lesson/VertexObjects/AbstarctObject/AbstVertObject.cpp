#include "AbstVertObject.h"

OGL::AbstVertObject::AbstVertObject()
{
	glGenBuffers(1, &(this->_ID));
}



bool OGL::AbstVertObject::isBinded()
{
	return this->_bind;
}


void OGL::AbstVertObject::setData(GLfloat *&data) noexcept
{
	this->_data = data;
}

[[nodiscard]] GLuint OGL::AbstVertObject::getId() noexcept
{
	return this->_ID;
}



OGL::AbstVertObject::~AbstVertObject()
{
	glDeleteBuffers(1, &(this->_ID));
}