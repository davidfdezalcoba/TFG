#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 vTexCoords;
out vec3 vNormal;
out vec3 vFragPos;
out vec3 vFragColor;

uniform float uMaxHeight;
uniform float uMinHeight;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uNormalMatrix;

const vec3 RED = vec3(1.0, 0.0, 0.0);
const vec3 GREEN = vec3(0.0, 1.0, 0.0);
const vec3 BLUE = vec3(0.0, 0.0, 1.0);

void main()
{
	float alpha;
	float middle = (uMaxHeight - uMinHeight) / 2;
	if (aPos.z > middle) {
		alpha = smoothstep(uMaxHeight, middle, aPos.z);	
		vFragColor = mix(RED, GREEN, alpha);	
	}
	else {
		alpha = smoothstep(middle, uMinHeight, aPos.z);	
		vFragColor = mix(GREEN, BLUE, alpha);	
	}

    vTexCoords = aTexCoords;    
  	vNormal = aNormal;
	vFragPos = vec3(uModel * vec4(aPos, 1.0)); 
	gl_Position =  uProjection * uView * vec4(vFragPos, 1.0);
}
