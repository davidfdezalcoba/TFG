#ifndef TERRAIN_H
#define TERRAIN_H

#include "shader.h"
#include "object.h"
#include "model.h"

#include <iostream>

class Terrain : public Object{
public:
	Terrain(float width, float height);
	void draw();
private:
	Shader terrainShader;
	Model dmodel;
	void setUniforms();
};

#endif