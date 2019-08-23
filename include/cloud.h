#ifndef CLOUD_H
#define CLOUD_H

#include "shader.h"
#include "object.h"
#include "scalarDataLoader.h"
#include <glfw3.h>

#include <iostream>

class Cloud : public Object{
public:
	Cloud();
	void draw();
	void processInput(GLFWwindow *window);
private:
	Shader cloudShader;
	ScalarDataLoader vl;
	float uMax;
	void setUniforms();
};

#endif
