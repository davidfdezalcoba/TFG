#include "beziercurve.h"
#include <glfw3.h>

BezierCurve :: BezierCurve(float width, float height) : 
	bezierShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/vertexshader.vs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/fragmentshader.frs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/geometryshader.grs"), 
	pointShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/pointshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/pointshader.frs"),
	axisShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/axisshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/axisshader.frs"), uNum(25),
	vLoader("/home/david/Projects/TFG/Project/resources/objects/bezier/bezier.vtx"),
	vLoader2("/home/david/Projects/TFG/Project/resources/objects/bezier/axis.vtx")
	{
		camera = Camera(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 225, -30);
		this->width = width;
	   	this->height = height;
	}

void BezierCurve :: draw(){
	setUniforms();
	glPointSize(9);
	pointShader.use();
	vLoader.Draw(pointShader, GL_POINTS);	
	glLineWidth(1);
	axisShader.use();
	vLoader2.Draw(axisShader, GL_LINES);	
	bezierShader.use();
	glLineWidth(3);
	vLoader.Draw(bezierShader, GL_LINES_ADJACENCY);	
}

void BezierCurve :: processInput(GLFWwindow *window){
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
		{uNum++;}
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{uNum--;}
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{vLoader.getNextActiveVertex();}
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{vLoader.moveVertexX(
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 0 : 1);}
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		{vLoader.moveVertexY(
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 0 : 1);}
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{vLoader.moveVertexZ(
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 0 : 1);}
}

void BezierCurve :: setUniforms(){
	projection = glm::perspective(glm::radians(camera.Zoom), this->width / this->height, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	lightPos = glm::vec3(0.0f);
	bezierShader.use();	
	bezierShader.setMat4("uModel", model);
	bezierShader.setMat4("uView", view);
	bezierShader.setMat4("uProjection", projection);
	bezierShader.setVec3("uViewPos", camera.Position);
	bezierShader.setVec3("uLight.position", lightPos);
	bezierShader.setInt("uNum", uNum);
	pointShader.use();	
	pointShader.setMat4("uModel", model);
	pointShader.setMat4("uView", view);
	pointShader.setMat4("uProjection", projection);
	pointShader.setVec3("uViewPos", camera.Position);
	pointShader.setVec3("uLight.position", lightPos);
	axisShader.use();	
	axisShader.setMat4("uModel", model);
	axisShader.setMat4("uView", view);
	axisShader.setMat4("uProjection", projection);
	axisShader.setVec3("uViewPos", camera.Position);
	axisShader.setVec3("uLight.position", lightPos);
}
