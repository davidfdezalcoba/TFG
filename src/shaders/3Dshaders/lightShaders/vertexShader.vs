#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 vTexCoords;
out vec3 vNormal;
out vec3 vFragPos;

uniform float aTime;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uNormalMatrix;

void main()
{
    vTexCoords = aTexCoords;    
  	vNormal = aNormal;
	vFragPos = vec3(uModel * vec4(aPos, 1.0)); 
	gl_Position =  uProjection * uView * uModel * vec4(aPos, 1.0);
}
