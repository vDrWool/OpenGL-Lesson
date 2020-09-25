#include "Shader.h"


template<GLenum type>
OGL::Shader<type>::Shader() {}

template<GLenum type>
OGL::Shader<type>::Shader(std::string sourcePath)
{
	this->_path = sourcePath.c_str();

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

//#ifdef DEBUG_
		std::string whatShader{};
		if (sourcePath.rfind(".vert.glsl") != std::string::npos)
			whatShader = "VERTEX_SHADER_SOURCE:";
		else if (sourcePath.rfind(".frag.glsl") != std::string::npos)
			whatShader = "FRAGMENT_SHADER_SOURCE:";
		else
			whatShader = "GEOMETRY_SHADER_SOURCE:";

		std::cout << "============================================"
			<< std::endl
			<< whatShader
			<< std::endl
			<< this->_shaderSource << std::endl
			<< "============================================"
			<< std::endl;
//#endif
		this->privateCreateShader();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << "Path:" << this->_path << std::endl;
	}
}


template<GLenum type>
[[nodiscard]] const char* OGL::Shader<type>::getShaderSource() const noexcept
{
	return this->_shaderSource;
}

template<GLenum type>
[[nodiscard]] GLuint OGL::Shader<type>::getID() const noexcept
{
	return this->_ID;
}


template<GLenum type>
OGL::Shader<type>::~Shader() noexcept
{
	glDeleteShader(this->_ID);
}


// (Private methods) =======================================================================================


template<GLenum type>
void OGL::Shader<type>::privateCreateShader()
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


template class OGL::Shader<GL_VERTEX_SHADER>;
template class OGL::Shader<GL_FRAGMENT_SHADER>;
template class OGL::Shader<GL_GEOMETRY_SHADER>;