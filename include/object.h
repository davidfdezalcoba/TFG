#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include <glfw3.h>

class Object{
	public:
		Object(){}
		virtual void draw() = 0;
		Camera camera;
		virtual void processInput(GLFWwindow * window) = 0;
		void setDeltaTime(float deltaTime){
			this->deltaTime = deltaTime;
		}
	protected:
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 lightPos;
		float width;
		float height;
		float deltaTime;
	private:
		virtual void setUniforms() = 0;
};

#endif
