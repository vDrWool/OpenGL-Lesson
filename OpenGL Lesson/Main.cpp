#include <iostream>
#include <string>
#include <random>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shaders/ShaderProgram/ShaderProgram.h"



auto processInput(GLFWwindow*) -> void;



auto main() -> int
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* mainWindow{ glfwCreateWindow(800, 640, "GLFW window", nullptr, nullptr) };
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

	glViewport(0, 0, 800, 640);
	
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


	OGL::VertexShader vShader("Shaders/ShaderSources/Vertex/vert1.vert.glsl");


	//===============================================================================
	

	OGL::FragmentShader fShader("Shaders/ShaderSources/Fragment/frag1.frag.glsl");


	//===============================================================================


	OGL::ShaderProgram progShader(vShader, fShader);


	//===============================================================================


	// Вершины примитива.
	GLfloat vertices1[] = {
		-0.1f,  0.1f,  0.0f,   1.0f, 0.0f, 0.0f,
		-0.9f,  0.1f,  0.0f,   0.0f, 1.0f, 0.0f,
		-0.5f,  0.9f,  0.0f,   0.0f, 0.0f, 1.0f
	};
	GLfloat vertices2[] = {
		 0.1f,  0.1f,  0.0f,   1.0f, 0.0f, 0.0f,
		 0.9f,  0.1f,  0.0f,   0.0f, 1.0f, 0.0f,
		 0.5f,  0.9f,  0.0f,   0.0f, 0.0f, 1.0f
	};


	GLuint VAO[2]{}, VBO[2]{};
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);



	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//===============================================================================

	
	std::default_random_engine gen{};
	std::uniform_real_distribution<float> rand(0.1f, 1.0f);
	

	glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
	while (!glfwWindowShouldClose(mainWindow)) 
	{
		processInput(mainWindow);

		glClear(GL_COLOR_BUFFER_BIT);

		progShader.use();


		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}


	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	glfwTerminate();
	return 0;
}

auto processInput(GLFWwindow* window) -> void
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		glfwSetWindowTitle(window, "Respect!");
}