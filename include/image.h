#ifndef IMAGE_H
#define IMAGE_H

#include <glad.h> 

#include <string>
#include <shader.h>
#include <iostream>

using namespace std;

unsigned int ImageFromFile(const char *path, bool gamma = false);

class Image
{
public:
	bool gammaCorrection;
	unsigned int texture;

	Image(string const &path, bool gamma = false);

	void Draw(Shader shader);

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

	void setupQuad();
};

unsigned int ImageFromFile(const char *path, bool gamma);

#endif
