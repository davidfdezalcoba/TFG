#include "BezierCurve.h"
#include <object.h>

BezierCurve :: BezierCurve(float width, float height) : 
	bezierShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/vertexshader.vs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/fragmentshader.frs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/geometryshader.grs"), 
	pointShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/pointshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/bezier/pointshader.frs"), uNum(25),
	vLoader("/home/david/Projects/TFG/Project/resources/objects/bezier/bezier.vtx") 
	{
		this->width = width;
	   	this->height = height;
	}

void BezierCurve :: draw(){
	setUniforms();
	glPointSize(9);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	pointShader.use();
	vLoader.Draw(pointShader, GL_POINTS);	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	bezierShader.use();
	vLoader.Draw(bezierShader, GL_LINES_ADJACENCY);	
}

void BezierCurve :: setUniforms(){
	projection = glm::perspective(glm::radians(camera.Zoom), this->width / this->height, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, -0.00f, -2.0f));
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
}