#include <glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <image.h>
#include <model.h>
#include <camera.h>
#include <modes.h>
#include <vertexLoader.h>
#include <object.h>
#include "BezierCurve.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Shader &shader);
int createWindow(GLFWwindow* & window);
void processHeights();
void reloadShader();
void setOptions(const Modes & mode);
void setUniforms(const Modes & mode);
Object* setupModel(const Modes & mode);
void draw(const Modes & mode, Object* obj);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const Modes MODE = bezier;

static GLFWwindow* window = nullptr;

Camera* camera = nullptr;
Object* obj = nullptr;

static Shader * shader = nullptr;
static Model * model = nullptr;
static VertexLoader * vLoader = nullptr;
GLenum PRIMITIVE = GL_TRIANGLES;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, char *argv[])
{
    createWindow(window);
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);
	setOptions(MODE);
	obj = setupModel(MODE);
	camera = &obj->camera;
    // render loop
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		
        processInput(window, *shader);

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Wireframe mode
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		draw(MODE, obj);

		//set uniforms in shader
		// shader->use();
		// setUniforms(MODE);
		// draw(MODE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clear all previously allocated resources
    glfwTerminate();
	delete shader;
	delete model;
    return 0;
}

void processInput(GLFWwindow *window, Shader &shader)
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
    if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
		{reloadShader();}
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

void reloadShader(){
	const char * vp = shader->vertexPath;
	const char * fp = shader->fragmentPath;
	const char * gp = shader->geometryPath;
	delete shader;
    shader = new Shader(vp, fp, gp);
}

void setOptions(const Modes & mode){
	switch(mode) {
		case terrain: 
			shader = new Shader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrain/notextures/vertexShader.vs",
				              "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrain/notextures/fragmentShader.frs");

			model = new Model("/home/david/Projects/TFG/Project/resources/objects/terrain/mars_valles_mar.stl");

			glfwSetCursorPosCallback(window, mouse_callback);
			glfwSetScrollCallback(window, scroll_callback);
			break;
		case bezier:
			//shader = new Shader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/vertexshader.vs",
			//	              "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/fragmentshader.frs",
			//	              "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/geometryshader.grs");

			//vLoader = new VertexLoader("/home/david/Projects/TFG/Project/resources/objects/bezier/bezier.vtx");

			glfwSetCursorPosCallback(window, mouse_callback);
			glfwSetScrollCallback(window, scroll_callback);
			break;	
		default: ;
	}
}

void setUniforms(const Modes & mode){
	//set model view and projection matrices
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 modelMatrix = glm::mat4(1.0f); 
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -0.00f, -15.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	glm::mat3 nanoNormal = glm::mat3(transpose(inverse(modelMatrix)));
	// setup light
	glm::mat4 lightModel = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(0.0, 0.0, 0.0);
	lightPos = lightModel * glm::vec4(lightPos, 1.0);

	switch(mode) {
		case terrain: 
			shader->setFloat("uMaxHeight", model->maxHeight);
			shader->setFloat("uMinHeight", model->minHeight);
			shader->setMat4("uModel", modelMatrix);
			shader->setMat4("uView", view);
			shader->setMat4("uProjection", projection);
			shader->setVec3("uViewPos", camera->Position);
			shader->setMat3("uNormalMatrix", nanoNormal);
			shader->setVec3("uLight.position",  lightPos);
			shader->setVec3("uLight.ambient",  0.1f, 0.1f, 0.1f);
			shader->setVec3("uLight.diffuse",  0.7f, 0.7f, 0.7f);
			shader->setVec3("uLight.specular", 0.4f, 0.4f, 0.4f);
			shader->setFloat("uShininess", 15.0f);
			break;
		case bezier:
			shader->setMat4("uModel", modelMatrix);
			shader->setMat4("uView", view);
			shader->setMat4("uProjection", projection);
			shader->setVec3("uViewPos", camera->Position);
			shader->setVec3("uLight.position",  lightPos);
			shader->setInt("uNum", 25);
			break;
		default:;	
	}
}	

Object* setupModel(const Modes & mode){
	switch(mode) {
		case terrain: 
			//model->Draw(*shader, PRIMITIVE);
			break;
		case bezier:
			return new BezierCurve(SCR_WIDTH, SCR_HEIGHT);
			break;
		default:;	
	}
	return nullptr;
}

void draw(const Modes & mode, Object* obj){
	switch(mode) {
		case terrain: 
			model->Draw(*shader, PRIMITIVE);
			break;
		case bezier:
			//vLoader->Draw(*shader, PRIMITIVE);
			obj->draw();
			break;
		default:;	
	}
}
