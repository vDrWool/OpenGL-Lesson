#include "ShaderProgram.h"


OGL::ShaderProgram::ShaderProgram(const VertexShader&& vShader,
								  const FragmentShader&& fShader,
								  const GeometryShader&& gShader) noexcept
{
	this->_ID = glCreateProgram();
	glAttachShader(this->_ID, vShader.getID());
	glAttachShader(this->_ID, fShader.getID());
	if (gShader.getID() != 0)
		glAttachShader(this->_ID, gShader.getID());
	glLinkProgram(this->_ID);

	GLint success{};
	glGetProgramiv(this->_ID, GL_LINK_STATUS, &success);
	if (GLchar infoLog[512]{}; !success)
	{
		glGetProgramInfoLog(this->_ID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}



void OGL::ShaderProgram::Bind(const GLuint id)
{
	glUseProgram(id);
}

void OGL::ShaderProgram::Unbind()
{
	glUseProgram(0);
}


const GLuint OGL::ShaderProgram::getID() const noexcept
{
	return this->_ID;
}



void OGL::ShaderProgram::setUniform1b(const std::string &name, bool value)
{
	glUniform1i(this->privateGetUniformLocation(name), static_cast<int>(value));
}

void OGL::ShaderProgram::setUniform1i(const std::string &name, int value)
{
	glUniform1i(this->privateGetUniformLocation(name), value);
}

void OGL::ShaderProgram::setUniform1f(const std::string& name, float value)
{
	glUniform1f(this->privateGetUniformLocation(name), value);
}

void OGL::ShaderProgram::setUniform4f(const std::string& name, float u1, float u2, float u3, float u4)
{
	glUniform4f(this->privateGetUniformLocation(name), u1, u2, u3, u4);
}



OGL::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->_ID);
}



GLint OGL::ShaderProgram::privateGetUniformLocation(const std::string& name)
{
	if (this->_uniformCache.find(name) != this->_uniformCache.end())
		return this->_uniformCache[name];

	auto location{ glGetUniformLocation(this->_ID, name.c_str()) };
	if (location == -1)
		std::cout << "WARNING::SHADERPROGRAM::UNIFORM::[\"" << name << "\"]_DOESN'T_EXIST!" << std::endl;
	
	this->_uniformCache[name] = location;
	return location;
}