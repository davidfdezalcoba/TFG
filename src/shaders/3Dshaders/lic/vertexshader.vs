#version 400 core
layout(location=0) in vec3 aPos;
layout(location=2) in vec2 aTexCoords;

out vec2 vTexCoords;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main(){
	vTexCoords = aTexCoords;
	gl_Position = vec4(aPos - 0.5, 1.0);
}
