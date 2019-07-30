#include "lic.h"

#include <iostream>
#include "stb_image.h"
using namespace std;

Lic :: Lic(float width, float height) : 
	licShader("/home/david/Projects/TFG/Project/src/shaders/3Dshaders/lic/vertexshader.vs", 
				"/home/david/Projects/TFG/Project/src/shaders/3Dshaders/lic/fragmentshader.frs"), 
		vLoader("/home/david/Projects/TFG/Project/resources/objects/lic/grid.txt", "/home/david/Projects/TFG/Project/resources/objects/lic/prueba.txt"),
		uLength(20)
	{
		this->noisetexture = ImageFromFile("/home/david/Projects/TFG/Project/resources/objects/lic/whitenoise.png", false);
		this->vectortexture = ImageFromFile("/home/david/Projects/TFG/Project/resources/objects/lic/vectortexture.jpg", false);
		this->width = width;
	   	this->height = height;
	}

void Lic :: draw(){
	setUniforms();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, noisetexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, vectortexture);
	licShader.use();	
	vLoader.Draw(licShader, GL_TRIANGLES);	
}

void Lic :: processInput(GLFWwindow *window){
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
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );}
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );}
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{if (uLength < 100) uLength++;}
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{if (uLength > 0)  uLength--;}
}

void Lic :: setUniforms(){
	projection = glm::perspective(glm::radians(camera.Zoom), this->width / this->height, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	model = glm::mat4(1.0f); 
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	lightPos = glm::vec3(0.0f);
	licShader.use();	
	licShader.setInt("texture1", 0);
	licShader.setInt("texture2", 1);
	licShader.setInt("uLength", uLength);
	licShader.setMat4("uModel", model);
	licShader.setMat4("uView", view);
	licShader.setMat4("uProjection", projection);
	licShader.setVec3("uViewPos", camera.Position);
	licShader.setVec3("uLight.position", lightPos);
}

unsigned int Lic :: ImageFromFile(const char *path, bool gamma)
{
    string filename = string(path);

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
