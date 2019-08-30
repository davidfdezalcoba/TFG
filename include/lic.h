#ifndef LIC_H
#define LIC_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"
#include <glfw3.h>

class Lic : public Object{
public:

	// Constructor
	Lic();

	// Inherited methods
	void draw();
	void processInput(GLFWwindow * window);

private:

	// Shader to use
	Shader licShader;	

	// Vertices loader
	VertexLoader vLoader;

	// Textures to use
	unsigned int noisetexture, vectortexture;

	// Length for the streamline computation
	int uLength;

	// Inherited methods
	void setUniforms();

	// Load an image from the file in path
	unsigned int ImageFromFile(const char *path, bool gamma);
};

#endif
