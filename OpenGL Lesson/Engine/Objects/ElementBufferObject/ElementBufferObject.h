#pragma once
#include "../../Utilities/OGL.h"


namespace OGL
{
	class ElementBufferObject
	{
	public:
		ElementBufferObject(const ElementBufferObject&) = delete;
		ElementBufferObject(const ElementBufferObject&&) = delete;

		ElementBufferObject& operator = (const ElementBufferObject&) = delete;
	public:
		ElementBufferObject(const GLuint* data, const GLsizeiptr size, GLenum usage);

		static void bind(const GLuint id);
		static void unBindAll();

		[[nodiscard]] inline GLuint getID() const noexcept;

		~ElementBufferObject();
	private:
		GLuint _ID{};
	};

	using EBO = ElementBufferObject;
}