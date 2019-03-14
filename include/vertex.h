#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position; // position
    glm::vec3 Normal; // normal
    glm::vec2 TexCoords; // texCoords
    glm::vec3 Tangent; // tangent
    glm::vec3 Bitangent; // bitangent
};

#endif
