#ifndef TERRAIN_H
#define TERRAIN_H

#include "shader.h"
#include "object.h"
#include "model.h"
#include <glfw3.h>

#include <iostream>

class Terrain : public Object{
public:

	// Constructor
	Terrain();

	// Inherited methods
	void draw();
	void processInput(GLFWwindow *window);

private:

	// Shader to use
	Shader terrainShader;

	// Model of the terrain to color
	Model dmodel;

	// Inherited method
	void setUniforms();
};

#endif
