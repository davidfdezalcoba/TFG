#include <glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <image.h>
#include <model.h>
#include <camera.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Shader &shader);
int createWindow(GLFWwindow* & window);
void processHeights();
void reloadShader(Shader &shader);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//set lightning
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
float ambientLight = 1.0;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, char *argv[])
{

    GLFWwindow* window = NULL;
    createWindow(window);
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);

    Shader marsShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrainshaders/notextures/vertexShader.vs",
                     "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrainshaders/notextures/fragmentShader.frs");

	Model mars("/home/david/Projects/TFG/Project/resources/objects/terrain/mars_valles_mar.stl");

    // render loop
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		
        processInput(window, marsShader);

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Wireframe mode
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//set model view and projection matrices
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f); 
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, -10.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glm::mat3 nanoNormal = glm::mat3(transpose(inverse(model)));
		// setup light
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightPos = glm::vec3(0.0, 0.0, 0.0);
		lightPos = lightModel * glm::vec4(lightPos, 1.0);

		//set uniforms in shader
		marsShader.use();
		marsShader.setFloat("uMaxHeight", mars.maxHeight);
		marsShader.setFloat("uMinHeight", mars.minHeight);
		marsShader.setMat4("uModel", model);
		marsShader.setMat4("uView", view);
		marsShader.setMat4("uProjection", projection);
		marsShader.setVec3("uViewPos", camera.Position);
		marsShader.setMat3("uNormalMatrix", nanoNormal);
		marsShader.setVec3("uLight.position",  lightPos);
		marsShader.setVec3("uLight.ambient",  0.1f, 0.1f, 0.1f);
		marsShader.setVec3("uLight.diffuse",  0.7f, 0.7f, 0.7f);
		marsShader.setVec3("uLight.specular", 0.7f, 0.7f, 0.7f);
		marsShader.setFloat("uShininess", 49.0f);
        mars.Draw(marsShader);

		//load image
		// imageShader.use();
		// image.Draw(imageShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, Shader &shader)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{glfwSetWindowShouldClose(window, true);}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{camera.ProcessKeyboard(FORWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{camera.ProcessKeyboard(BACKWARD, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{camera.ProcessKeyboard(LEFT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{camera.ProcessKeyboard(RIGHT, deltaTime);}
    if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
		{reloadShader(shader);}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

int createWindow(GLFWwindow* & window)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return 0;
}

void processHeights(){

}

void reloadShader(Shader &shader){
    shader = Shader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrainshaders/vertexShader.vs",
                     "/home/david/Projects/TFG/Project/src/shaders/3Dshaders/terrainshaders/fragmentShader.frs");
}
