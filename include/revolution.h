#ifndef REVOLUTION_H	
#define REVOLUTION_H	

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"

class Revolution : public Object{
public:
	Revolution();
	void draw();
	void processInput(GLFWwindow * window);
private:
	Shader revolutionShader;	
	Shader pointShader;
	float uNum;
	VertexLoader vLoader;
	VertexLoader vLoader2;
	void setUniforms();
};

#endif
