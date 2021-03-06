#include "VertexArrayObject.h"

OGL::VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &(this->_ID));
}

void OGL::VertexArrayObject::Bind(const GLuint id)
{
    glBindVertexArray(id);
}

void OGL::VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}

void OGL::VertexArrayObject::addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& vbl)
{
    VAO::Bind(this->_ID);
    VBO::Bind(vbo.getID());

    const auto& elements{ vbl.getElements() };
    GLuint pointer{};

    for (GLuint i{ 0 }; i < elements.size(); i++)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elements[i].count, elements[i].type,
            elements[i].normolised, vbl.getStride(), reinterpret_cast<void*>(pointer));

        pointer += elements[i].count * VertexBufferElement::getSizeOfType(elements[i].type);
    }
}

GLuint OGL::VertexArrayObject::getID() const noexcept
{
    return this->_ID;
}

OGL::VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &(this->_ID));
}
