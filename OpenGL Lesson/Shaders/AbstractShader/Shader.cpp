#include "Shader.h"

OGL::Shader::Shader(std::string sourcePath, GLenum type)
{
	this->_path = sourcePath;

	try
	{
		std::ifstream vShaderFile{};
		std::stringstream vShaderStream{};
		std::string tempSource{};

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		vShaderFile.open(sourcePath);
		vShaderStream << vShaderFile.rdbuf();
		vShaderFile.close();

		tempSource = vShaderStream.str();
		this->_shaderSource = tempSource.c_str();

		std::cout << "============================================"
			      << std::endl
			      << this->_shaderSource << std::endl 
			      << "============================================"
			      << std::endl;

		this->privateCreateShader(type);
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << "Path:" << this->_path << std::endl;
	}
} 



[[nodiscard]] const char* OGL::Shader::getShaderSource() const noexcept
{
	return this->_shaderSource;
}

[[nodiscard]] GLuint OGL::Shader::getID() const noexcept
{
	return this->_ID;
}



OGL::Shader::~Shader() noexcept
{
	glDeleteShader(this->_ID);
}



// (Private methods) =======================================================================================



void OGL::Shader::privateCreateShader(GLenum type)
{
	this->_ID = glCreateShader(type);
	glShaderSource(this->_ID, 1, &(this->_shaderSource), nullptr);
	glCompileShader(this->_ID);

	GLint success{};
	glGetShaderiv(this->_ID, GL_COMPILE_STATUS, &success);
	if (char infoLog[512]{}; !success)
	{
		if (type == GL_VERTEX_SHADER)
		{
			glGetShaderInfoLog(this->_ID, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			glGetShaderInfoLog(this->_ID, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
}