#include "negative.h"
#include <glad.h>
#include <glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Negative :: Negative() : 
		negativeShader("/home/david/Projects/TFG/Project/src/shaders/imageShaders/negative/vertexShader.vs",
			   	"/home/david/Projects/TFG/Project/src/shaders/imageShaders/negative/fragmentShader.frs"),
	   	image("/home/david/Projects/TFG/Project/resources/images/negativo.jpg") {}

void Negative :: draw(){
	setUniforms();
	image.Draw(negativeShader);
}

void Negative :: processInput(GLFWwindow *window){
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
}

void Negative :: setUniforms(){
	negativeShader.use();
	negativeShader.setInt("texture1", 0);
	negativeShader.setFloat("uT", 1);
}
