#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include <glfw3.h>
#include <iostream>

class Object{
	public:
		Object(){}
		virtual void draw() = 0;
		Camera camera;
		virtual void processInput(GLFWwindow * window) = 0;

		virtual void setOptions(GLFWwindow * window);

		void setDeltaTime(float deltaTime);

	protected:
		const unsigned int SCR_WIDTH = 1366;
		const unsigned int SCR_HEIGHT = 768;
		float lastX = SCR_WIDTH / 2.0f;
		float lastY = SCR_HEIGHT / 2.0f;
		bool firstMouse = true;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 lightPos;
		float deltaTime;

		static void default_mouse_callback(GLFWwindow* window, double xpos, double ypos);
	private:
		virtual void setUniforms() = 0;
};

#endif
