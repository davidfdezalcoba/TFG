#include "cloud.h"
#include <glad.h>
#include <glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Cloud :: Cloud() : 
	cloudShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/cloud/vertexShader.vs",
				  "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/cloud/fragmentShader.frs"),
	vl("/home/david/Projects/TFG/Project/resources/objects/cloud/scalar.csv", false),
	uMax(0)
	{
		camera = Camera(glm::vec3(3.0f, 3.0f, 1.6f), glm::vec3(0.0f, 1.0f, 0.0f), 225, -30);
	}

void Cloud :: draw(){
	setUniforms();
	vl.Draw(cloudShader, GL_POINTS);
}

void Cloud :: processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{glfwSetWindowShouldClose(window, true);}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{camera.ProcessKeyboard(FORWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{camera.ProcessKeyboard(BACKWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{camera.ProcessKeyboard(LEFT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{camera.ProcessKeyboard(RIGHT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{uMax++;}
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{uMax--;}
}

void Cloud :: setUniforms(){
	//setup model, view and projection matrices
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	cloudShader.use();	
	cloudShader.setMat4("uModel", model);
	cloudShader.setMat4("uView", view);
	cloudShader.setMat4("uProjection", projection);
	cloudShader.setFloat("uMaxData", vl.maxData);
	cloudShader.setFloat("uMax", uMax);
}
