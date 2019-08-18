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

	VertexLoader(string const &path, string const &indexpath="", bool gamma=false) : gammaCorrection(gamma)
	{
		loadVertices(path);
		loadIndices(indexpath);
		setupVertices();
	}		

	void Draw(Shader shader, GLenum primitive)
	{
		glBindVertexArray(VAO);
		if (!drawfromindices)
			glDrawArrays(primitive, 0, vertices.size());
		else 
			glDrawElements(primitive, 3*indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void getPreviousActiveVertex(){
		vertices[activeVertex].Color = glm::vec3(1.0f, 1.0f, 1.0f);
		activeVertex = (activeVertex - 1);
		if (activeVertex == -1) activeVertex = numVertices - 1;
		vertices[activeVertex].Color = glm::vec3(1.0f, 0.0f, 0.0f);
		setupVertices();
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
	int numVertices, numIndices;
	int activeVertex = 0;
	bool drawfromindices = false;
	vector<MyVertex> vertices;
	vector<glm::uvec3> indices;
	unsigned int VAO, VBO, EBO;

	// This function loads vertices
	void loadVertices(const string &path){
		ifstream in(path);
		auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
		MyVertex vertexToBeLoaded;
		cin >> this->numVertices;
		int numCoords;
		cin >> numCoords;
		for(int i = 0; i < numVertices; i++){
			cin >> vertexToBeLoaded.Position.x;
			cin >> vertexToBeLoaded.Position.y;
			if (numCoords == 3) cin >> vertexToBeLoaded.Position.z;
			else vertexToBeLoaded.Position.z = 0.0f;
			vertexToBeLoaded.Color = glm::vec3(1.0f, 1.0f, 1.0f);
			vertexToBeLoaded.TexCoords = glm::vec2(vertexToBeLoaded.Position.x, vertexToBeLoaded.Position.y);
			this->vertices.push_back(vertexToBeLoaded);
		}
		this->vertices[0].Color = glm::vec3(1.0f, 0.0f, 0.0f);
		std::cin.rdbuf(cinbuf); //reset to standard input again
	}

	// This function loads indices to EBO if there is a path provided
	void loadIndices(const string & indexpath){
		if ( indexpath != "" ) {
			drawfromindices = true;
			ifstream in2(indexpath);	
			auto cinbuf = std::cin.rdbuf(in2.rdbuf()); //save old buf and redirect std::cin to casos.txt
			glm::uvec3 indexToBeLoaded;
			cin >> this->numIndices;
			for(int i = 0; i < numIndices; i++){
				cin >> indexToBeLoaded.x;
				cin >> indexToBeLoaded.y;
				cin >> indexToBeLoaded.z;
				this->indices.push_back(indexToBeLoaded);
			}
			std::cin.rdbuf(cinbuf); //reset to standard input again
		}
	}

	void setupVertices()
	{
		// VAO data
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// VBO data
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 8 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		// vertex atribute pointers
		// vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);

		// vertex color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));

		// Vertex texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

		// EBO data
		if(drawfromindices){
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(glm::uvec3), &(indices[0]), GL_STATIC_DRAW);
		}
	}
};

#endif
