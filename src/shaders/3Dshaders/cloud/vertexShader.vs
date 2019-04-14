#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aScalar;

out float vScalar;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform float uMaxData;

void main()
{
	vScalar = aScalar;
	gl_PointSize = pow((smoothstep(0.0, uMaxData, aScalar) + 1), 2);
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
