#ifndef BEZIERSURFACE_H
#define BEZIERSURFACE_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"
#include <glfw3.h>

class BezierSurface : public Object{
public:

	//Constructor
	BezierSurface();

	// Methods from base class
	void draw();
	void processInput(GLFWwindow * window);
	void setOptions(GLFWwindow * window);

private:

	// Shaders to use
	Shader bezierShader;	
	Shader pointShader;
	Shader axisShader;

	// Z value for the last active vertex
	GLfloat activevertexdepth;

	// Tessellation levels
	float uOuter02;
	float uOuter13;
	float uInner0;
	float uInner1;

	// Specifies whether the camera should move
	bool move;

	// Control points loader
	VertexLoader vLoader;
	// Axis points loader
	VertexLoader vLoader2;

	// Method from base class
	void setUniforms();

	// Specific callbacks for this object
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif
