#include "beziersurface.h"

#include <iostream>
using namespace std;

BezierSurface :: BezierSurface(float width, float height, void (*mc)(GLFWwindow* window, double xpos, double ypos)) : 
	bezierShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/vertexshader.vs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/fragmentshader.frs",
				 nullptr,
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/tescontrolshader.tecs", 
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/tesevalshader.tees"), 
	pointShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/pointshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/pointshader.frs"),
	axisShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/axisshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/axisshader.frs"),
		uOuter02(10), uOuter13(10), uInner0(10), uInner1(10),
		lastX(width / 2.0), lastY(height / 2.0),
		move(true), firstMouse(true),
	vLoader("/home/david/Projects/TFG/Project/resources/objects/beziersurface/bezier.vtx"),
	vLoader2("/home/david/Projects/TFG/Project/resources/objects/beziersurface/axis.vtx")
	{
		camera = Camera(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 225, -30);
		this->width = width;
	   	this->height = height;
		mouse_callback = mc;
	}

void BezierSurface :: draw(){
	setUniforms();
	// glPointSize(9);
	pointShader.use();
	vLoader.Draw(pointShader, GL_POINTS);	
	axisShader.use();
	vLoader2.Draw(axisShader, GL_LINES);	
	bezierShader.use();
	glPatchParameteri(GL_PATCH_VERTICES, 16);
	vLoader.Draw(bezierShader, GL_PATCHES);	
}

void BezierSurface :: processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{glfwSetWindowShouldClose(window, true);}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(FORWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(BACKWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(LEFT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(RIGHT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{uOuter02++;uOuter13++;uInner0++;uInner1++;}
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{uOuter02--;uOuter13--;uInner0--;uInner1--;}
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );}
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );}
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//		{vLoader.getNextActiveVertex();}
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

void BezierSurface::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	BezierSurface* bs = static_cast<BezierSurface*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{bs->vLoader.getNextActiveVertex();}
}

void BezierSurface::setOptions( GLFWwindow *window ){
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
}

void BezierSurface :: setUniforms(){
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
	bezierShader.setFloat("uOuter02", uOuter02);
	bezierShader.setFloat("uOuter13", uOuter13);
	bezierShader.setFloat("uInner0", uInner0);
	bezierShader.setFloat("uInner1", uInner1);
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
