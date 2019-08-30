#ifndef MYVERTEX_H
#define MYVERTEX_H

#include <glm/glm.hpp>

struct MyVertex {
    glm::vec3 Position; // position
    glm::vec3 Color; // color
	glm::vec2 TexCoords; // teture coordinates
};

#endif
