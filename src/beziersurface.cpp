#include "beziersurface.h"

BezierSurface :: BezierSurface(float width, float height) : 
	bezierShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/vertexshader.vs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/fragmentshader.frs",
				 "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/geometryshader.grs"), 
	pointShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/pointshader.vs",
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/beziersurface/pointshader.frs"), uNum(25),
	vLoader("/home/david/Projects/TFG/Project/resources/objects/beziersurface/bezier.vtx"),
	vLoader2("/home/david/Projects/TFG/Project/resources/objects/beziersurface/axis.vtx")
	{
		camera = Camera(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 225, -30);
		this->width = width;
	   	this->height = height;
	}

void BezierSurface :: draw(){
	setUniforms();
	glPointSize(9);
	pointShader.use();
	vLoader.Draw(pointShader, GL_POINTS);	
	glLineWidth(1);
	vLoader2.Draw(pointShader, GL_LINES);	
	bezierShader.use();
	glLineWidth(3);
	vLoader.Draw(bezierShader, GL_LINES_ADJACENCY);	
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
	bezierShader.setInt("uNum", uNum);
	pointShader.use();	
	pointShader.setMat4("uModel", model);
	pointShader.setMat4("uView", view);
	pointShader.setMat4("uProjection", projection);
	pointShader.setVec3("uViewPos", camera.Position);
	pointShader.setVec3("uLight.position", lightPos);
}
