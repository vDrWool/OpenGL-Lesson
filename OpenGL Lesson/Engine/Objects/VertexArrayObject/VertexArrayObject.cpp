#include "VertexArrayObject.h"

OGL::VertexArrayObject::VertexArrayObject()
{
    GLCall(glGenVertexArrays(1, &(this->_ID)));
}

void OGL::VertexArrayObject::bind(const GLuint id)
{
    GLCall(glBindVertexArray(id));
}

void OGL::VertexArrayObject::unBindAll()
{
    GLCall(glBindVertexArray(0));
}

void OGL::VertexArrayObject::addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& vbl)
{
    VAO::bind(this->_ID);
    VBO::bind(vbo.getID());

    const auto& elements{ vbl.getElements() };
    GLuint pointer{};

    for (GLuint i{ 0 }; i < elements.size(); i++)
    {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type,
            elements[i].normolised, vbl.getStride(), reinterpret_cast<void*>(pointer)));

        pointer += elements[i].count * VertexBufferElement::getSizeOfType(elements[i].type);
    }
}

GLuint OGL::VertexArrayObject::getID() const noexcept
{
    return this->_ID;
}

OGL::VertexArrayObject::~VertexArrayObject()
{
    GLCall(glDeleteVertexArrays(1, &(this->_ID)));
}
