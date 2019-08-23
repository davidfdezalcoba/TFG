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

		virtual void setOptions(GLFWwindow * window){
			glfwSetWindowUserPointer(window, this);
			glfwSetCursorPosCallback(window, default_mouse_callback);
		}

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
		
		const unsigned int SCR_WIDTH = 1366;
		const unsigned int SCR_HEIGHT = 768;
		float lastX = SCR_WIDTH / 2.0f;
		float lastY = SCR_HEIGHT / 2.0f;
		bool firstMouse = true;

		static void default_mouse_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Object* obj = static_cast<Object*>(glfwGetWindowUserPointer(window));
		    if (obj->firstMouse)
		    {
		        obj->lastX = xpos;
		        obj->lastY = ypos;
		        obj->firstMouse = false;
		    }
		
		    float xoffset = xpos - obj->lastX;
		    float yoffset = obj->lastY - ypos; // reversed since y-coordinates go from bottom to top
		
		    obj->lastX = xpos;
		    obj->lastY = ypos;
		
		    obj->camera.ProcessMouseMovement(xoffset, yoffset);
		}

	private:

		virtual void setUniforms() = 0;

};

#endif
