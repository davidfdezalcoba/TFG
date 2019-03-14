#ifndef VERTEXLOADER_H
#define VERTEXLOADER_H

#include <glad.h> 

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include "shader.h"
#include <iostream>
#include <vector>

using namespace std;

class VertexLoader
{
public:
	bool gammaCorrection;

	VertexLoader(string const &path, bool gamma=false) : gammaCorrection(gamma)
	{
		ifstream in(path);
		auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
		glm::vec3 vertexToBeLoaded;
		cin >> this->numVertices;
		for(int i = 0; i < numVertices; i++){
			cin >> vertexToBeLoaded.x;
			cin >> vertexToBeLoaded.y;
			cin >> vertexToBeLoaded.z;
			this->vertices.push_back(vertexToBeLoaded);
		}
		std::cin.rdbuf(cinbuf); //reset to standard input again
		setupVertices();
	}		

	void Draw(Shader shader, GLenum primitive)
	{
		glBindVertexArray(VAO);
		glDrawArrays(primitive, 0, vertices.size());
        glBindVertexArray(0);
	}
private:
	int numVertices;
	vector<glm::vec3> vertices;
	unsigned int VAO, VBO, EBO;

	void setupVertices()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		//vertex atribute pointers
		//vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		// glBindVertexArray(0);
	}
};

#endif
