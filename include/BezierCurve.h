#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <iostream>
#include <shader.h>
#include <object.h>
#include <vertexLoader.h>

class BezierCurve : public Object{
public:
	BezierCurve(float width, float height);
	void draw();
private:
	Shader bezierShader;	
	Shader pointShader;
	float uNum;
	VertexLoader vLoader;
	void setUniforms();
};

#endif
