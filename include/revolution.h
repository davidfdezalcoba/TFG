#ifndef REVOLUTION_H	
#define REVOLUTION_H	

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"

class Revolution : public Object{
public:

	// Constructor
	Revolution();

	// Inherited methods
	void draw();
	void processInput(GLFWwindow * window);

private:

	// Shaders to use
	Shader revolutionShader;	
	Shader pointShader;

	// Number of vértices to draw in revolution
	float uNum;

	// Curve vertices loader
	VertexLoader vLoader;
	//Axis vertices loader
	VertexLoader vLoader2;

	// Inherited method
	void setUniforms();
};

#endif
