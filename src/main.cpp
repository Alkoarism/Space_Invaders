#include "OpenGL\renderer.h"
#include "OpenGL\camera.h"
#include "OpenGL\texture.h"
#include "bitmap_font.h"

using std::vector;

// function declarations ------------------------------------------------------
void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

// global variables -----------------------------------------------------------
const int screenWidth = 600, screenHeight = 800;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

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

	glEnable(GL_DEPTH_TEST);

	// vertices definition -------------------------------------------------------
	vector<float> simpleQuad = {
		//vertex			//texture		
		// Bottom vertices
		 0.5f,  0.5f, 0.0f,	//top right
		 0.5f, -0.5f, 0.0f,	//bottom right
		-0.5f, -0.5f, 0.0f,	//bottom left
		-0.5f,  0.5f, 0.0f,	//top left
	};

	vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};

	// vertex and buffers configurations -----------------------------------------
	VertexArray quadVAO;

	quadVAO.Bind();
	VertexBuffer quad_vb(&simpleQuad[0], sizeof(simpleQuad) * simpleQuad.size());
	VertexBufferLayout quad_vbl;
	quad_vbl.Push<float>(3);
	quadVAO.AddBuffer(quad_vb, quad_vbl);

	IndexBuffer ib(&indices[0], indices.size());

	// texture handling ----------------------------------------------------------
	//TextureLayout tl(GL_TEXTURE_2D, GL_RGBA);

	//tl.AddPar(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//tl.AddPar(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//tl.AddPar(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//tl.AddPar(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Texture texture(tl, "res\\textures\\alien_triangle_0.png");

	// initialization before rendering -------------------------------------------
	Renderer::LoadShader("test", "res\\shaders\\main_vert.shader", "res\\shaders\\main_frag.shader");
	
	glm::mat4 projection = glm::perspective
	(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	Renderer::GetShader("test").SetUniform("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	Renderer::GetShader("test").SetUniform("view", view);
	Renderer::GetShader("test").SetUniform("model", glm::mat4(1.0f));
	//glActiveTexture(GL_TEXTURE0);

	// render loop (happens every frame) -----------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// -> frame time tracker
		Renderer::FrameTimeTracker();

		// -> rendering commands and configuration
		Renderer::RenderConfig(1.0f, 1.0f, 1.0f, 1.0f);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		// ---> space configurations and rendering
		//texture.Bind();
		glm::vec4 color = glm::vec4(1.0f);
		color.y = sin(glfwGetTime());
		color.x = cos(glfwGetTime());
		Renderer::GetShader("test").SetUniform("textColor", color);

		Renderer::Render(quadVAO, ib, Renderer::GetShader("test"));

		//The model global variable is used to render stuff on the right place

		// -> check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}