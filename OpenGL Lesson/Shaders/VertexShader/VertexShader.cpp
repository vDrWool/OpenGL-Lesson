#include <fstream>
#include <sstream>

#include "VertexShader.h"

OGL::VertexShader::VertexShader(std::string sourcePath) : Shader(sourcePath, GL_VERTEX_SHADER) {}