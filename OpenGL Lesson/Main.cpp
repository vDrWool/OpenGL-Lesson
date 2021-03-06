#include <iostream>
#include <string>
#include <random>



#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Engine/Utilities/stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Engine/Renderer.h"


auto processInput(GLFWwindow*) -> void;



auto main() -> int
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* mainWindow{ glfwCreateWindow(640, 640, "GLFW window", nullptr, nullptr) };
	if (mainWindow == nullptr)
	{
		std::cerr << "ERROR: Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "ERROR: Failed to initialize GLAD!" << std::endl;
		glfwTerminate();
		return -2;
	}

	glViewport(0, 0, 640, 640);

	glfwSetFramebufferSizeCallback(
		mainWindow,
		[](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);
	glfwSetCursorPosCallback(
		mainWindow,
		[](GLFWwindow* window, double xPos, double yPos)
		{
			glfwGetCursorPos(window, &xPos, &yPos);
			std::ostringstream title{};
			title << "(" << yPos << " ," << xPos << ")";

			glfwSetWindowTitle(window, title.str().c_str());
		}
	);


	//===============================================================================


	OGL::ShaderProgram progShader(
		OGL::VertexShader("Engine/Shaders/ShadersSources/Vertex/vert1.vert.glsl"),
		OGL::FragmentShader("Engine/Shaders/ShadersSources/Fragment/frag1.frag.glsl")
	);


	//===============================================================================


	stbi_set_flip_vertically_on_load(true);

	GLuint texture{};
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width{}, height{}, nrChannels{};
	unsigned char* data{ stbi_load("Engine/Textures/TextureSources/image.jpg", &width, &height, &nrChannels, 0) };
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture!" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);


	//===============================================================================


	// ������� ���������.
	GLfloat VBOsData[][32] = {
		{
			// Coord.             // Color.           //TextureCoord.  
			0.1f,  0.1f,  0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
			0.1f,  0.9f,  0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
			0.9f,  0.9f,  0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
			0.9f,  0.1f,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f
	   },
	   {
		   -0.1f,  0.1f,  0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		   -0.1f,  0.9f,  0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		   -0.9f,  0.9f,  0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		   -0.9f,  0.1f,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f
	   },
	   {
		   -0.1f, -0.1f,  0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		   -0.1f, -0.9f,  0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		   -0.9f, -0.9f,  0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		   -0.9f, -0.1f,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f
	   },
	   {
			0.1f, -0.1f,  0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
			0.1f, -0.9f,  0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
			0.9f, -0.9f,  0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
			0.9f, -0.1f,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f
	   }
	};

	GLuint eboIndexes[] = {
		0, 1, 2,
		2, 3, 0
	};

	OGL::VAO vao[4]{};
	OGL::VBO vbo[4] = {
		{ VBOsData[0], sizeof(VBOsData[0]), GL_STATIC_DRAW },
		{ VBOsData[1], sizeof(VBOsData[1]), GL_STATIC_DRAW },
		{ VBOsData[2], sizeof(VBOsData[2]), GL_STATIC_DRAW },
		{ VBOsData[3], sizeof(VBOsData[3]), GL_STATIC_DRAW }
	};

	OGL::VBL layout{};
	layout.push<GLfloat>(3);
	layout.push<GLfloat>(3);
	layout.push<GLfloat>(2);
	for (auto i{ 0 }; i < 4; i++)
	{
		vao[i].addBuffer(vbo[i], layout);
	}

	OGL::VBO::Unbind();
	OGL::VAO::Unbind();

	OGL::EBO ebo{ eboIndexes, sizeof(eboIndexes), GL_STATIC_DRAW };

	OGL::EBO::Unbind();
	//===============================================================================


	std::default_random_engine gen{};
	std::uniform_real_distribution<float> rand(0.1f, 1.0f);


	OGL::ShaderProgram::Bind(progShader.getID());
	progShader.setUniform1i("ourTexture", 0);
	OGL::ShaderProgram::Unbind();


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.4f, 0.5f, 0.5f, 1.0f);
	while (!glfwWindowShouldClose(mainWindow))
	{
		processInput(mainWindow);

		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		for (auto i{ 0 }; i < 4; i++)
		{
			OGL::Renderer::Draw(vao[i], ebo, progShader);
		}

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

auto processInput(GLFWwindow* window) -> void
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}