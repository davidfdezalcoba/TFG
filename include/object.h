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

		// The camera object to use in this scene
		Camera camera;

		// Constructor
		Object(){}

		// Draw command
		virtual void draw() = 0;

		// Processes input continuously.
		virtual void processInput(GLFWwindow * window) = 0;

		// Set the callbacks to use in this scene
		virtual void setOptions(GLFWwindow * window);

		// Sets the deltaTime, aka the time the last frame took to render
		void setDeltaTime(float deltaTime);

	protected:

		// Dimensions of the viewport. 
		// TODO also defined in tfg.cpp Must refactor
		const unsigned int SCR_WIDTH = 1366;
		const unsigned int SCR_HEIGHT = 768;

		// last_. The last position of the mouse in coordinate _
		float lastX = SCR_WIDTH / 2.0f;
		float lastY = SCR_HEIGHT / 2.0f;

		// Whether is the first mouse move or not
		bool firstMouse = true;

		// Model, view and projection matrices used for all scenes
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 lightPos;

		// The time it took to render the last frame
		float deltaTime;

		// Default callbacks. FPS and zoom
		static void default_mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void default_scroll_callback(GLFWwindow* window, double xpos, double ypos);

	private:

		// Set the uniforms needed for the shaders
		virtual void setUniforms() = 0;
};

#endif
