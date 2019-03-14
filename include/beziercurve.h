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
private:
	Shader bezierShader;	
	Shader pointShader;
	float uNum;
	VertexLoader vLoader;
	VertexLoader vLoader2;
	void setUniforms();
};

#endif
