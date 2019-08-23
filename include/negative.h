#ifndef NEGATIVE_H
#define NEGATIVE_H

#include "shader.h"
#include "object.h"
#include "image.h"
#include <glfw3.h>

#include <iostream>

class Negative : public Object{
public:
	Negative();
	void draw();
	void processInput(GLFWwindow *window);
private:
	Shader negativeShader;
	Image image;
	float width, height;
	void setUniforms();
};

#endif
