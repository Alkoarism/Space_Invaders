#include "OpenGL\renderer.h"
#include "OpenGL\camera.h"
#include "OpenGL\texture.h"

#include "space_invaders.h"

using std::vector;

// function declarations ------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// global variables -----------------------------------------------------------
const unsigned int screenWidth = 600, screenHeight = 800;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::unique_ptr<SpaceInvaders> spaceInvaders;

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
		(screenWidth,  screenHeight, "OpenGL Space_Invaders_Clone", NULL, NULL);
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

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// initialization before rendering -------------------------------------------
	spaceInvaders.reset(new SpaceInvaders(screenWidth, screenHeight));

	// render loop (happens every frame) -----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// -> frame time tracker
		Renderer::FrameTimeTracker();

		// ---> space configurations and rendering
		//The model, projection and camera variables are handled by the game class
		spaceInvaders->ProcessInput(Renderer::GetDeltaTime());

		spaceInvaders->Update(Renderer::GetDeltaTime());

		// -> rendering commands and configuration
		Renderer::RenderConfig();
		spaceInvaders->Render();

		// -> check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			spaceInvaders->keys[key] = true;
		else if (action = GLFW_RELEASE)
			spaceInvaders->keys[key] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}