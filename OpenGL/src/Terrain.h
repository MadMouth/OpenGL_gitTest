#pragma once
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

/* Math library */
#include "glm-0.9.9.8/glm/glm.hpp"
#include "glm-0.9.9.8/glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "glm-0.9.9.8/glm/gtc/type_ptr.hpp"

#define xSize 100
#define zSize 100

class Terrain
{
private:
        GLuint TerrainVAO;
        GLuint TerrainVBO;
public:
    void terrainInitialization();

    glm::vec3* returnVec(glm::vec3 CubeVec);

    void terrainDraw();
};


