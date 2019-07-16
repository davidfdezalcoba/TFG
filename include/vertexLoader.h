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
#include "myvertex.h"

using namespace std;

class VertexLoader
{
public:
	bool gammaCorrection;

	VertexLoader(string const &path, bool gamma=false) : gammaCorrection(gamma)
	{
		ifstream in(path);
		auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
		MyVertex vertexToBeLoaded;
		vertexToBeLoaded.Color = glm::vec3(1.0f, 0.0f, 0.0f);
		cin >> this->numVertices;
		for(int i = 0; i < numVertices; i++){
			cin >> vertexToBeLoaded.Position.x;
			cin >> vertexToBeLoaded.Position.y;
			cin >> vertexToBeLoaded.Position.z;
			this->vertices.push_back(vertexToBeLoaded);
			vertexToBeLoaded.Color = glm::vec3(1.0f, 1.0f, 1.0f);
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
	
	void getNextActiveVertex(){
		vertices[activeVertex].Color = glm::vec3(1.0f, 1.0f, 1.0f);
		activeVertex = (activeVertex + 1) % numVertices;
		vertices[activeVertex].Color = glm::vec3(1.0f, 0.0f, 0.0f);
		setupVertices();
	}

	void moveVertexX(int dir){
		vertices[activeVertex].Position.x += (dir == 0)? 0.1 : -0.1;
		setupVertices();
	}

	void moveVertexY(int dir){
		vertices[activeVertex].Position.y += (dir == 0)? 0.1 : -0.1;
		setupVertices();
	}

	void moveVertexZ(int dir){
		vertices[activeVertex].Position.z += (dir == 0)? 0.1 : -0.1;
		setupVertices();
	}

private:
	int numVertices;
	int activeVertex = 0;
	vector<MyVertex> vertices;
	unsigned int VAO, VBO, EBO;

	void setupVertices()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 2 * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		//vertex atribute pointers
		//vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
		//vertex color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

		// glBindVertexArray(0);
	}
};

#endif
