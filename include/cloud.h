#ifndef CLOUD_H
#define CLOUD_H

#include "shader.h"
#include "object.h"
#include "scalarDataLoader.h"
#include <glfw3.h>

#include <iostream>

class Cloud : public Object{
public:

	// Constructor
	Cloud();

	// Inherited methods
	void draw();
	void processInput(GLFWwindow *window);

private:

	// Shader to use
	Shader cloudShader;

	// Data points loader
	ScalarDataLoader vl;

	// Limit for point rendering
	float uMax;

	// Inherited method
	void setUniforms();
};

#endif
