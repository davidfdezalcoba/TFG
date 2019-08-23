#include "beziercurve.h"
#include <glfw3.h>

BezierCurve :: BezierCurve() : 
	bezierShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/vertexshader.vs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/fragmentshader.frs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/geometryshader.grs"), 
	pointShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/pointshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/pointshader.frs"),
	axisShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/axisshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/axisshader.frs"), move(true), uNum(25),
	vLoader("/home/david/Projects/TFG/Project/resources/objects/bezier/bezier.vtx"),
	vLoader2("/home/david/Projects/TFG/Project/resources/objects/bezier/axis.vtx")
	{
		camera = Camera(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 225, -30);
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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(FORWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(BACKWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(LEFT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && move)
		{camera.ProcessKeyboard(RIGHT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{uNum++;}
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{uNum--;}
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

void BezierCurve::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	BezierCurve* bs = static_cast<BezierCurve*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		if(mods & GLFW_MOD_SHIFT) bs->vLoader.getNextActiveVertex();
		else bs->vLoader.getPreviousActiveVertex();
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS){
		bs->move = !bs->move;
		glfwSetInputMode(window, GLFW_CURSOR, (!bs->move ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED));
		glfwSetCursorPosCallback(window, (!bs->move ? NULL : default_mouse_callback));
		glfwSetCursorPos(window, bs->lastX, bs->lastY);
	}
}

// Callback to change active vertex
void BezierCurve::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	BezierCurve* bs = static_cast<BezierCurve*>(glfwGetWindowUserPointer(window));

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);	

		glm::vec3 p0 = glm::unProject(glm::vec3(xpos,bs->SCR_HEIGHT-ypos,0), bs->view*bs->model, bs->projection, glm::vec4(0,0,bs->SCR_WIDTH,bs->SCR_HEIGHT));
		glm::vec3 p1 = glm::unProject(glm::vec3(xpos,bs->SCR_HEIGHT-ypos,1), bs->view*bs->model, bs->projection, glm::vec4(0,0,bs->SCR_WIDTH,bs->SCR_HEIGHT));

		vector<MyVertex> posiciones = bs->vLoader.getVertices();

		float minDist = 0.2;
		for(unsigned int i = 0; i < posiciones.size(); i++){
			glm::vec3 comp = posiciones[i].Position;
			float dist = glm::length(glm::cross(comp-p0, comp-p1)) / glm::length(p1-p0);
			if(dist < minDist){
				bs->vLoader.setActiveVertex(i);
				glReadPixels( xpos, bs->SCR_HEIGHT-ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &bs->activevertexdepth);	
				minDist = dist;
			}
		}
	}
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);	
		glm::vec3 p0 = glm::unProject(glm::vec3(xpos,bs->SCR_HEIGHT-ypos,bs->activevertexdepth), bs->view*bs->model, bs->projection, glm::vec4(0,0,bs->SCR_WIDTH,bs->SCR_HEIGHT));
		bs->vLoader.setActiveVertexPosition(p0);
	}
}

void BezierCurve::setOptions( GLFWwindow *window ){
	Object::setOptions(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void BezierCurve :: setUniforms(){

	// Model, view, projection matrices
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

	bezierShader.use();	
	bezierShader.setMat4("uModel", model);
	bezierShader.setMat4("uView", view);
	bezierShader.setMat4("uProjection", projection);
	bezierShader.setInt("uNum", uNum);
	pointShader.use();	
	pointShader.setMat4("uModel", model);
	pointShader.setMat4("uView", view);
	pointShader.setMat4("uProjection", projection);
	axisShader.use();	
	axisShader.setMat4("uModel", model);
	axisShader.setMat4("uView", view);
	axisShader.setMat4("uProjection", projection);
}
