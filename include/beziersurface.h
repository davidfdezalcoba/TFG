#ifndef BEZIERSURFACE_H
#define BEZIERSURFACE_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"
#include <glfw3.h>

class BezierSurface : public Object{
public:
	BezierSurface(float width, float height, void (*mc)(GLFWwindow* window, double xpos, double ypos));
	void draw();
	void processInput(GLFWwindow * window);
private:
	Shader bezierShader;	
	Shader pointShader;
	Shader axisShader;
	float uOuter02;
	float uOuter13;
	float uInner0;
	float uInner1;
	float lastX, lastY;
	bool move, firstMouse;
	void (*mouse_callback)(GLFWwindow* window, double xpos, double ypos);
	VertexLoader vLoader;
	VertexLoader vLoader2;
	void setUniforms();
};

#endif
