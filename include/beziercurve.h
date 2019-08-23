#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"

class BezierCurve : public Object{
public:
	BezierCurve();
	void draw();
	void processInput(GLFWwindow * window);
	void setOptions( GLFWwindow *window );
private:
	Shader bezierShader;	
	Shader pointShader;
	Shader axisShader;
	GLfloat activevertexdepth;
	bool move;
	float uNum;
	VertexLoader vLoader;
	VertexLoader vLoader2;
	void setUniforms();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif
