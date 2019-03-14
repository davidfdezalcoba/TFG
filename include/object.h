#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.h>

class Object{
	public:
		Object(){}
		virtual void draw() = 0;
		Camera camera;
	protected:
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 lightPos;
		float width;
		float height;
	private:
		virtual void setUniforms() = 0;
};

#endif
