#ifndef BEZIERSURFACE_H
#define BEZIERSURFACE_H

#include <iostream>
#include "shader.h"
#include "vertexLoader.h"
#include "object.h"

class BezierSurface : public Object{
public:
	BezierSurface(float width, float height);
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
