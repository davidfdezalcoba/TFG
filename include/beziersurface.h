#ifndef BEZIERSURFACE_H
#define BEZIERSURFACE_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"
#include <glfw3.h>

class BezierSurface : public Object{
public:
	BezierSurface();
	void draw();
	void processInput(GLFWwindow * window);
	void setOptions(GLFWwindow * window);
private:
	Shader bezierShader;	
	Shader pointShader;
	Shader axisShader;
	GLfloat activevertexdepth;
	float uOuter02;
	float uOuter13;
	float uInner0;
	float uInner1;
	bool move;
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	VertexLoader vLoader;
	VertexLoader vLoader2;
	void setUniforms();
};

#endif
