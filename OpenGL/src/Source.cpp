#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"


#include "glm-0.9.9.8/glm/glm.hpp"
#include "glm-0.9.9.8/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.9.8/glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Terrain.h"
#include "Camera.h"
float yValue = 0.0f;

bool terrainshow = true;
int main(void)
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    GLFWwindow* window;

    if (!glfwInit())
        return -1;


    window = glfwCreateWindow(1980, 1080, "GOVNA_KUSOK_HD_360_SUCKCOCK", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);




    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint normalVBO;
    glGenBuffers(1, &normalVBO);

    Terrain terrain;
    terrain.terrainInitialization();

    Camera camera(window);

    Shader Myshader("C:/ALL_OpenGL/OpenGLSourceFiles/VS_OpenGL_1/OpenGL/OpenGL/VertexShader.txt", // terrain
                    "C:/ALL_OpenGL/OpenGLSourceFiles/VS_OpenGL_1/OpenGL/OpenGL/FragmentShader.txt");

    Shader lightingShader("C:/ALL_OpenGL/OpenGLSourceFiles/VS_OpenGL_1/OpenGL/OpenGL/LightVertexShader.txt", //cube
                          "C:/ALL_OpenGL/OpenGLSourceFiles/VS_OpenGL_1/OpenGL/OpenGL/LightFragmentShader.txt");
  


    //CUBE TEST
    GLuint CubeVAO;
    glGenVertexArrays(1, &CubeVAO);
    glBindVertexArray(CubeVAO);

    GLuint CubeVBO;
    glCreateBuffers(1, &CubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);




    Myshader.use();
    Myshader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    Myshader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.146f, 0.129f, 0.129f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        Myshader.use();

        camera.use(window);
        glm::mat4 view = camera.getView();


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f + yValue), glm::vec3(0.0f, 1.0f, 0.0f));


        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(90.0f), 1980.0f / 1080.0f, 0.1f, 300.0f);


        Myshader.setMat4("model", model);
        Myshader.setMat4("view", view);
        Myshader.setMat4("projection", projection);
        Myshader.setVec3("lightPos", glm::vec3(6 * (float)glfwGetTime() + 1.0f, 1.0f, 8.0f));

        //Draw Terrain
        if (terrainshow)
         terrain.terrainDraw();

        
        //Draw Cube
        lightingShader.use();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(6 * (float)glfwGetTime()+1.0f, 1.0f, 8.0f));


        glm::mat4 allMatrices = projection * view * model;
        lightingShader.setMat4("allMatrices", allMatrices);
        lightingShader.setVec3("lightPos", 6*(float)glfwGetTime() + 1.0f, 1.0f, 8.0f);


        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glm::vec3* TerrainNorm = terrain.returnVec(glm::vec3(6 * (float)glfwGetTime() + 1.0f, 1.0f, 8.0f));
        glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainNorm), TerrainNorm, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);


        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }




    glfwTerminate();
};