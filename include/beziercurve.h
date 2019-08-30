#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"

class BezierCurve : public Object{
public:

	// Constructor
	BezierCurve();

	// Methods from base class
	void draw();
	void processInput(GLFWwindow * window);
	void setOptions( GLFWwindow *window );

private:

	// Shaders to use
	Shader bezierShader;	
	Shader pointShader;
	Shader axisShader;

	// Z value of the last active vertex
	GLfloat activevertexdepth;

	// Specifies whether to move the camera
	bool move;

	// Number of segments to divide de curve into
	float uNum;

	// Control points loader
	VertexLoader vLoader;
	// Axis points loader
	VertexLoader vLoader2;

	// Method from base class
	void setUniforms();

	// Specific callbacks used by this object
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

};

#endif
