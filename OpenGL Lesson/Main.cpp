#include <iostream>
#include <string>
#include <sstream>
#include <random>


#include <glad/glad.h>
#include <GLFW/glfw3.h>



auto processInput(GLFWwindow*) -> void;



auto main() -> int
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* mainWindow{ glfwCreateWindow(800, 640, "GLFW window", nullptr, nullptr) };
	if (mainWindow == nullptr)
	{
		std::cout << "ERROR: Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "ERROR: Failed to initialize GLAD!" << std::endl;
		glfwTerminate();
		return -1;
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


	// Код шейдера, и создание объекта шейдера.
	const char* vertexShaderCode =  R"(#version 330 core
									   layout (location = 0) in vec3 aPos;
									   layout (location = 1) in vec3 aColor;
									   out vec3 ourColor;
									   void main()
									   {
									      gl_Position = vec4(aPos.x, 1.0 - aPos.y, aPos.z, 1.0);
									      ourColor = aColor;
								       })";
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Прикрепляем код шейдера к объекту.
	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	// Компилируем шейдер.
	glCompileShader(vertexShader);

	// Проверка на то: скомпилировался ли шейдер.
	GLint success{};
	char infoLog[512];
	// Есть ли ошибка?
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// Получение ошибки.
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		success = 1;
		memset(infoLog, 0, sizeof(infoLog));
	}


	//===============================================================================


	const char* fragmentShaderCode = "#version 330 core\n"
									 "out vec4 FragColor;\n"
									 "in vec3 ourColor;"
									 "void main()\n"
									 "{\n"
									 "   FragColor = vec4(ourColor, 1.0);\n"
									 "}\n\0";
	// Создание фрагментного шейдера (как и с вершиным).
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		success = 1;
		memset(infoLog, 0, sizeof(infoLog));
	}


	const char* fragmentShaderCode2 = "#version 330 core\n"
									  "out vec4 FragColor;\n"
									  "in vec3 ourColor;\n"
									  "void main()\n"
									  "{\n"
									  "   FragColor = vec4(ourColor, 1.0);\n"
									  "}\n\0";

	GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderCode2, nullptr);
	glCompileShader(fragmentShader2);

	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		success = 1;	
		memset(infoLog, 0, sizeof(infoLog));
	}
	

	//===============================================================================


	// Создание шейдерной программы.
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		success = 1;
		memset(infoLog, 0, sizeof(infoLog));
	}


	GLuint shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glGetShaderiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram2, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		success = 1;
		memset(infoLog, 0, sizeof(infoLog));
	}


	//===============================================================================


	// Освобождение памяти.
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);


	//===============================================================================


	// Вершины примитива.
	GLfloat vertices1[] = {
		-0.1,  0.1,  0.0,   1.0f, 0.0f, 0.0f,
		-0.9,  0.1,  0.0,   0.0f, 1.0f, 0.0f,
		-0.5,  0.9,  0.0,   0.0f, 0.0f, 1.0f
	};
	GLfloat vertices2[] = {
		 0.1,  0.1,  0.0,   1.0f, 0.0f, 0.0f,
		 0.9,  0.1,  0.0,   0.0f, 1.0f, 0.0f,
		 0.5,  0.9,  0.0,   0.0f, 0.0f, 1.0f
	};


	// Создание объекта вершиного массива.
	GLuint VAO[2]{}, VBO[2]{};
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	{
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	{
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//===============================================================================


	
	std::default_random_engine gen{};
	std::uniform_real_distribution<float> rand(0.1f, 1.0f);
	

	glClearColor(0.5f, 0.2f, 0.1f, 1.0f);
	while (!glfwWindowShouldClose(mainWindow)) 
	{
		processInput(mainWindow);

		glClear(GL_COLOR_BUFFER_BIT);
		 
		{
			glUseProgram(shaderProgram);

			{
				auto newFragmentShaderColor = glGetUniformLocation(shaderProgram, "newColor1");
				glUniform4f(newFragmentShaderColor, 0.4f, 0.7f, 0.1f, 1.0f);
			}

			glBindVertexArray(VAO[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		
		{
			glUseProgram(shaderProgram2);

			{
				auto newFragmentShaderColor = glGetUniformLocation(shaderProgram2, "newColor2");
				glUniform4f(newFragmentShaderColor, 1.0f, 0.5f, 0.9f ,1.0f);
			}

			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}


	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	glDeleteProgram(shaderProgram);
	
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