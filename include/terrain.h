#ifndef TERRAIN_H
#define TERRAIN_H

#include "shader.h"
#include "object.h"
#include "model.h"
#include <glfw3.h>

#include <iostream>

class Terrain : public Object{
public:
	Terrain();
	void draw();
	void processInput(GLFWwindow *window);
private:
	Shader terrainShader;
	Model dmodel;
	void setUniforms();
};

#endif
