#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBI_FAILURE_USERMSG
#define STBI_ONLYJPEG

#include "Shader.h"

#include <iostream>

// function declarations ------------------------------------------------------
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// global variables -----------------------------------------------------------
const int screenWidth = 800, screenHeight = 600;

int main() {
	// glfw: initialize and configure --------------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw: window creation and setup -------------------------------------------
	GLFWwindow* window = glfwCreateWindow
		(screenWidth,  screenHeight, "OpenGL standard template", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// glfw: setup
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader myShader("res\\shaders\\vertex.shader", "res\\shaders\\fragment.shader");

	// vertices definition -------------------------------------------------------
	float vertices_sq[] = {
		//vertex			//texture		
		// Bottom vertices
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	//top right
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	//bottom right
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	//bottom left
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	//top left

		// Top vertices
		0.5f,  0.5f,  -0.5f,  1.0f, 1.0f,	//top right
		0.5f, -0.5f,  -0.5f,  1.0f, 0.0f,	//bottom right
	   -0.5f, -0.5f,  -0.5f,  0.0f, 0.0f,	//bottom left
	   -0.5f,  0.5f,  -0.5f,  0.0f, 1.0f,	//top left
	};

	unsigned int indices[] = {
		//top		//bottom	//right		//left		//front		//back
		0, 1, 3,	4, 5, 7,	0, 1, 4,	2, 3, 6,	1, 2, 5,	0, 3, 4,
		1, 2, 3,	5, 6, 7, 	1, 4, 5,	3, 6, 7,	2, 5, 6,	4, 3, 7
	};

	// objects and buffer configurations -----------------------------------------
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_sq), vertices_sq, GL_STATIC_DRAW);

	//AttribPointer(attribute, components, type, ???, total size of components, offset)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer
		(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// texture handling ----------------------------------------------------------
	// this section could be reduced to a function or a specialized class
	unsigned int texture[2];
	glGenTextures(1, &texture[0]);
	glGenTextures(1, &texture[1]);
	
	//procedure refering to texture 1
	//set the texture wrapping / filtering options		glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load and generate the texture
	int img_width, img_height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = 
		stbi_load("res\\container.jpg", &img_width, &img_height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		const char* failLog = stbi_failure_reason();
		std::cout << "FAILED_TO_LOAD_TEXTURE\n" << failLog << std::endl;
	}
	stbi_image_free(data);

	//procedure referring to texture 2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load and generate the texture
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("res\\awesomeface.png", &img_width, &img_height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		const char* failLog = stbi_failure_reason();
		std::cout << "FAILED_TO_LOAD_TEXTURE\n" << failLog << std::endl;
	}
	stbi_image_free(data);

	// initialization before rendering -------------------------------------------
	myShader.use();
	glUniform1i(glGetUniformLocation(myShader.ID, "myTexture"), 0);
	myShader.setInt("myTexture2", 1);

	// render loop (happens every frame) -----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// -> frame time tracker
		// -> input handling
		processInput(window);

		// -> rendering commands and configuration
		glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.use();

		// ---> texture configurations
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		// ---> space configurations and rendering
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// -> check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}