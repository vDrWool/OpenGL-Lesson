#include "OGLdebug.h"

auto GLClearError() -> void
{
	while (glGetError() != GL_NO_ERROR);
}

auto GLLogCall(const char* func, const char* file, int line) -> bool
{
	while (GLenum error = glGetError())
	{
		std::cout << std::hex << "ERROR::" << "[ " << error << " ]:" <<
			"    FUNC::" << "[ " << func << " ]" <<
			"    FILE::" << "[ " << file << " ]" <<
			"    LINE::" << "[ " << line << " ]" << std::endl;

		return false;
	}

	return true;
}