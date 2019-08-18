#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"

class BezierCurve : public Object{
public:
	BezierCurve(float width, float height);
	void draw();
	void processInput(GLFWwindow * window);
	void setOptions( GLFWwindow *window );
private:
	Shader bezierShader;	
	Shader pointShader;
	Shader axisShader;
	float uNum;
	VertexLoader vLoader;
	VertexLoader vLoader2;
	void setUniforms();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
