#ifndef NEGATIVE_H
#define NEGATIVE_H

#include "shader.h"
#include "object.h"
#include "image.h"
#include <glfw3.h>

#include <iostream>

class Negative : public Object{
public:

	// Constructor
	Negative();

	// Inherited methods
	void draw();
	void processInput(GLFWwindow *window);

private:

	// Shader to use
	Shader negativeShader;

	// Image to compute the negative from
	Image image;

	// Dimensions of the image
	float width, height;

	// Inherited method
	void setUniforms();
};

#endif
