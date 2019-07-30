#ifndef LIC_H
#define LIC_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"
#include <glfw3.h>

class Lic : public Object{
public:
	Lic(float width, float height);
	void draw();
	void processInput(GLFWwindow * window);
private:
	Shader licShader;	
	VertexLoader vLoader;
	unsigned int noisetexture, vectortexture;
	int uLength;
	void setUniforms();
	unsigned int ImageFromFile(const char *path, bool gamma);
};

#endif
