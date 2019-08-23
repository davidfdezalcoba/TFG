#include "revolution.h"
#include <glfw3.h>

Revolution :: Revolution() : 
	revolutionShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/revolution/vertexshader.vs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/revolution/fragmentshader.frs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/revolution/geometryshader.grs"), 
	pointShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/revolution/pointshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/revolution/pointshader.frs"), uNum(25),
	vLoader("/home/david/Projects/TFG/Project/resources/objects/revolution/curve.vtx"),
	vLoader2("/home/david/Projects/TFG/Project/resources/objects/revolution/axis.vtx")
	{
		camera = Camera(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 225, -30);
	}

void Revolution :: draw(){
	setUniforms();
	glLineWidth(4);
	pointShader.use();
	vLoader.Draw(pointShader, GL_LINE_STRIP);	
	glLineWidth(1);
	vLoader2.Draw(pointShader, GL_LINES);	
	revolutionShader.use();
	vLoader.Draw(revolutionShader, GL_LINE_STRIP);	
}

void Revolution :: processInput(GLFWwindow *window){
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
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );}
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );}
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{uNum++;}
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{uNum--;}

}

void Revolution :: setUniforms(){
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	lightPos = glm::vec3(0.0f);
	revolutionShader.use();	
	revolutionShader.setMat4("uModel", model);
	revolutionShader.setMat4("uView", view);
	revolutionShader.setMat4("uProjection", projection);
	revolutionShader.setVec3("uViewPos", camera.Position);
	revolutionShader.setVec3("uLight.position", lightPos);
	revolutionShader.setInt("uNum", uNum);
	pointShader.use();	
	pointShader.setMat4("uModel", model);
	pointShader.setMat4("uView", view);
	pointShader.setMat4("uProjection", projection);
	pointShader.setVec3("uViewPos", camera.Position);
	pointShader.setVec3("uLight.position", lightPos);
}
