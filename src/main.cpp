#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "texture.h"
#include "texture_layout.h"

#include <iostream>

// function declarations ------------------------------------------------------
void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

// global variables -----------------------------------------------------------
const int screenWidth = 600, screenHeight = 800;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = screenWidth / 2, lastY = screenHeight / 2;
float fov = 45.0;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
		(screenWidth,  screenHeight, "OpenGL Space_Invaders", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// glfw: setup
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader myShader("dep\\shaders\\vertex.shader", "dep\\shaders\\fragment.shader");

	// vertices definition -------------------------------------------------------
	float vertices_quad[] = {
		//vertex			//texture		
		0.55f,  0.4f,  0.0f,  1.0f, 1.0f,	//top right
		0.55f, -0.4f,  0.0f,  1.0f, 0.0f,	//bottom right
	   -0.55f, -0.4f,  0.0f,  0.0f, 0.0f,	//bottom left
	   -0.55f,  0.4f,  0.0f,  0.0f, 1.0f,	//top left
	};

	unsigned int indices[] = {
		//squad indices
		0, 1, 2,
		0, 2, 3
	};

	glm::vec3 aliensTransformations[] = {
		glm::vec3(1.5f, 0.0f, 0.0f),
		glm::vec3(3.0f, 0.0f, 0.0f),
		glm::vec3(4.5f, 0.0f, 0.0f),
		glm::vec3(6.0f, 0.0f, 0.0f),
		glm::vec3(7.5f, 0.0f, 0.0f),
	};

	// vertex and buffers configurations -----------------------------------------
	unsigned int VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer vb(vertices_quad, sizeof(vertices_quad));
	IndexBuffer ib(indices, 6);

	//AttribPointer(attribute, components, type, ???, total size of components, offset)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer
		(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// texture handling ----------------------------------------------------------
	TextureLayout tl(GL_TEXTURE_2D);

	tl.AddPar(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	tl.AddPar(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	tl.AddPar(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	tl.AddPar(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Texture textures[] = {
		Texture(tl, "res\\sprites\\alien_square_0.png"),
		Texture(tl, "res\\sprites\\alien_square_1.png"),
	};

	// initialization before rendering -------------------------------------------
	myShader.use();
	myShader.setInt("myTexture", 0);
	myShader.setInt("myTexture2", 1);

	bool text_cng = false;
	float elapsedTime = glfwGetTime();
	myShader.setFloat("fade", 0.0f);

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture[1]);

	//glTexParameteri(m_Layout.GetType(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(m_Layout.GetType(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(m_Layout.GetType(), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(m_Layout.GetType(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// render loop (happens every frame) -----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// -> frame time tracker
		const float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		elapsedTime += deltaTime;

		// -> input handling
		processInput(window);

		// -> rendering commands and configuration
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.use();

		// ---> texture configurations
		if (text_cng) {
			textures[0].Bind();
		}
		else {
			textures[1].Bind();
		}

		if (elapsedTime > 0.5) {
			text_cng = !text_cng;
			elapsedTime = 0;
		}

		// ---> space configurations and rendering
		glBindVertexArray(VAO);

		glm::mat4 projection = glm::perspective
			(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		glm::mat4 view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		for (unsigned int i = 0; i < 5; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, aliensTransformations[i]);
			myShader.setMat4("model", model);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		// -> check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.ProcessMouseScroll(yOffset);
}