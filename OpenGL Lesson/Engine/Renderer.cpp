#include "Renderer.h"

void OGL::Renderer::Draw(const VertexArrayObject& vao, const ElementBufferObject& ebo, const ShaderProgram& sp)
{
	OGL::ShaderProgram::Bind(sp.getID());
	OGL::VAO::Bind(vao.getID());
	OGL::EBO::Bind(ebo.getID());

	glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
}