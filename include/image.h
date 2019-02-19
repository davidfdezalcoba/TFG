#ifndef IMAGE_H
#define IMAGE_H

#include <glad.h> 
//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>
#include <shader.h>
#include <iostream>

using namespace std;

unsigned int ImageFromFile(const char *path, bool gamma=false);

class Image
{
public:
	bool gammaCorrection;
	unsigned int texture;

	Image(string const &path, bool gamma=false) : gammaCorrection(gamma)
	{
		setupQuad();	
		texture = ImageFromFile(path.c_str());
	}		

	void Draw(Shader shader)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
	}
private:
	float vertices[20] = {
		 1.0f,  1.0f, 0.0f,     1.0f, 1.0f,  // top right
    	 1.0f, -1.0f, 0.0f,     1.0f, 0.0f,  // bottom right
    	-1.0f, -1.0f, 0.0f,     0.0f, 0.0f,  // bottom left
    	-1.0f,  1.0f, 0.0f,     0.0f, 1.0f  // top left
	};

	unsigned int indices[6] = {  // note that we start from 0!
	    0, 1, 3,   // first triangle
	    1, 2, 3    // second triangle
	};

	unsigned int VAO, VBO, EBO;

	void setupQuad()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//vertex atribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);

		//Texture attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));

		// glBindVertexArray(0);
	}
};

unsigned int ImageFromFile(const char *path, bool gamma)
{
    string filename = string(path);

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
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

#endif
