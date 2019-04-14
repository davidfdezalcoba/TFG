#ifndef SCALARDATALOADER_H
#define SCALARDATALOADER_H

#include <glad.h> 

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include "shader.h"
#include <iostream>
#include <vector>

struct ScalarVertex{
	glm::vec3 position;
	float scalar;
};

using namespace std;

class ScalarDataLoader
{
public:
	bool gammaCorrection;

	ScalarDataLoader(string const &path, bool gamma=false) : gammaCorrection(gamma)
	{
		ifstream in(path);
		auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
		ScalarVertex vertexToBeLoaded;
		cin >> this->numVertices;
		for(int i = 0; i < numVertices; i++){
			cin >> vertexToBeLoaded.position.x;
			cin >> vertexToBeLoaded.position.y;
			cin >> vertexToBeLoaded.position.z;
			cin >> vertexToBeLoaded.scalar;
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
	vector<ScalarVertex> vertices;
	unsigned int VAO, VBO, EBO;

	void setupVertices()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ScalarVertex), &vertices[0], GL_STATIC_DRAW);

		//vertex atribute pointers
		//vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ScalarVertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ScalarVertex), (void*)sizeof(glm::vec3));

		// glBindVertexArray(0);
	}
};

#endif
