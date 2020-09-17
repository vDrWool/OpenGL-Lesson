#include "ShaderProgram.h"

OGL::ShaderProgram::ShaderProgram(const VertexShader& vShader, const FragmentShader& fShader) noexcept
{
	this->_ID = glCreateProgram();
	glAttachShader(this->_ID, vShader.getID());
	glAttachShader(this->_ID, fShader.getID());
	glLinkProgram(this->_ID);

	GLint success{};
	glGetShaderiv(this->_ID, GL_LINK_STATUS, &success);
	if (GLchar infoLog[512]{}; success == GL_FALSE)
	{
		glGetProgramInfoLog(this->_ID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}



void OGL::ShaderProgram::use() const noexcept
{
	glUseProgram(this->_ID);
}



void OGL::ShaderProgram::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->_ID, name.c_str()), static_cast<int>(value));
}

void OGL::ShaderProgram::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(this->_ID, name.c_str()), value);
}

void OGL::ShaderProgram::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->_ID, name.c_str()), value);
}



OGL::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->_ID);
}