#pragma once
#include "VAO.h"

OGL::VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &(this->_ID));
}



bool OGL::VertexArrayObject::isBinded() noexcept
{
	return this->_bind;
}


void OGL::VertexArrayObject::bind()
{
	glBindVertexArray(this->_ID);

	this->_bind = true;
}

void OGL::VertexArrayObject::unbind()
{
	glBindVertexArray(0);
	this->_bind = false;
}

void OGL::VertexArrayObject::init(GLfloat* vboData, GLfloat* eboIndexes = nullptr)
{
	if (!(this->isBinded()))
		this->bind();

	this->_VBO.setData(vboData);
	this->_VBO.bind();
	this->_VBO.use(GL_STATIC_DRAW);

	this->_EBO.setData(eboIndexes);
	this->_EBO.bind();
	this->_EBO.use(GL_STATIC_DRAW);

	this->unbind();
}

void OGL::VertexArrayObject::vertexAttib(GLuint index, GLuint size, GLsizei stride, const void* pointer)
{
	if (!this->isBinded())
		this->bind();

	glVertexAttribPointer(1, size, GL_FLOAT, GL_FALSE, stride, pointer);
}