#include <glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "modes.h"

#include "terrain.h"
#include "beziercurve.h"
#include "beziersurface.h"
#include "negative.h"
#include "cloud.h"
#include "revolution.h"
#include "lic.h"

#include <iostream>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
int createWindow(GLFWwindow* & window);
void setOptions(const Modes & mode);
Modes selectmode(char * mode);
Object* setupModel(const Modes & mode);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static GLFWwindow* window = nullptr;

Camera* camera = nullptr;
Object* obj = nullptr;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, char *argv[])
{
	Modes MODE = (argc > 1)? selectmode(argv[1]) : revolution;

    createWindow(window);
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
	setOptions(MODE);
	obj = setupModel(MODE);
	obj->setOptions(window);
	camera = &obj->camera;
    // render loop
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		obj->setDeltaTime(deltaTime);
        lastFrame = currentFrame;
		
        obj->processInput(window);

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//wireframe mode
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		obj->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clear all previously allocated resources
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{glfwSetWindowShouldClose(window, true);}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{camera->ProcessKeyboard(FORWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{camera->ProcessKeyboard(BACKWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{camera->ProcessKeyboard(LEFT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{camera->ProcessKeyboard(RIGHT, deltaTime);}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}

int createWindow(GLFWwindow* & window)
{
	if (glfwInit() == GLFW_FALSE)
	{
		fprintf(stderr, "Failed to initialize GLFW");
		return -1;
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return 0;
}

void setOptions(const Modes & mode){
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

Object* setupModel(const Modes & mode){
	switch(mode) {
		case terrain: 
			return new Terrain(SCR_WIDTH, SCR_HEIGHT);
			break;
		case bezier:
			return new BezierCurve(SCR_WIDTH, SCR_HEIGHT);
			break;
		case beziersurface:
			return new BezierSurface(SCR_WIDTH, SCR_HEIGHT);
			break;
		case negative:
			return new Negative(SCR_WIDTH, SCR_HEIGHT);
			break;
		case cloud:
			return new Cloud(SCR_WIDTH, SCR_HEIGHT);
			break;
		case revolution:
			return new Revolution(SCR_WIDTH, SCR_HEIGHT);
			break;
		case lic:
			return new Lic(SCR_WIDTH, SCR_HEIGHT);
			break;
		default:;	
	}
	return nullptr;
}

Modes selectmode(char * mode){
	if (strncmp(mode, "terrain", 7) == 0) return terrain;
	else if (strncmp(mode, "bezier", 7) == 0) return bezier;
	else if (strncmp(mode, "bsurface", 7) == 0) return beziersurface;
	else if (strncmp(mode, "negative", 7) == 0) return negative;
	else if (strncmp(mode, "cloud", 7) == 0) return cloud;
	else if (strncmp(mode, "revolution", 7) == 0) return revolution;
	else if (strncmp(mode, "lic", 7) == 0) return lic;
	else return revolution;
}
