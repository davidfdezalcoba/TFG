#include "terrain.h"
#include <glad.h>
#include <glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Terrain :: Terrain() : 
	terrainShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrain/notextures/vertexShader.vs",
				  "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrain/notextures/fragmentShader.frs"),
	dmodel("/home/david/Projects/TFG/Project/resources/objects/terrain/mars_valles_mar.stl", false) {}

void Terrain :: draw(){
	setUniforms();
	dmodel.Draw(terrainShader, GL_TRIANGLES);
}

void Terrain :: processInput(GLFWwindow *window){
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

void Terrain :: setUniforms(){
	//setup model, view and projection matrices
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -15.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	glm::mat3 normal = glm::mat3(transpose(inverse(model)));
	lightPos = glm::vec3(0.0f);

	terrainShader.use();	
	terrainShader.setFloat("uMaxHeight", dmodel.maxHeight);
	terrainShader.setFloat("uMinHeight", dmodel.minHeight);
	terrainShader.setMat4("uModel", model);
	terrainShader.setMat4("uView", view);
	terrainShader.setMat4("uProjection", projection);
	terrainShader.setVec3("uViewPos", camera.Position);
	terrainShader.setMat3("uNormalMatrix", normal);
	terrainShader.setVec3("uLight.position",  lightPos);
	terrainShader.setVec3("uLight.ambient",  0.1f, 0.1f, 0.1f);
	terrainShader.setVec3("uLight.diffuse",  0.7f, 0.7f, 0.7f);
	terrainShader.setVec3("uLight.specular", 0.4f, 0.4f, 0.4f);
	terrainShader.setFloat("uShininess", 15.0f);
}
