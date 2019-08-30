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
void processInput(GLFWwindow* window);
int createWindow(GLFWwindow* & window);
Modes selectmode(char * mode);
Object* setupModel(const Modes & mode);

const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

static GLFWwindow* window = nullptr;

Camera* camera = nullptr;
Object* obj = nullptr;

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

	// Configure object to be drawn
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

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f); //background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		obj->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clear all previously allocated resources
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Trabajo de Fin de Grado", NULL, NULL);
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

Object* setupModel(const Modes & mode){
	switch(mode) {
		case terrain: 
			return new Terrain();
			break;
		case bezier:
			return new BezierCurve();
			break;
		case beziersurface:
			return new BezierSurface();
			break;
		case negative:
			return new Negative();
			break;
		case cloud:
			return new Cloud();
			break;
		case revolution:
			return new Revolution();
			break;
		case lic:
			return new Lic();
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
