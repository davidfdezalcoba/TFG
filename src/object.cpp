#include "object.h"
using namespace std;

void Object::setOptions(GLFWwindow * window){
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, default_mouse_callback);
	glfwSetScrollCallback(window, default_scroll_callback);
}

void Object::setDeltaTime(float deltaTime){
	this->deltaTime = deltaTime;
}

void Object::default_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Object* obj = static_cast<Object*>(glfwGetWindowUserPointer(window));
    obj->camera.ProcessMouseScroll(yoffset);
}

void Object::default_mouse_callback(GLFWwindow* window, double xpos, double ypos){
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
