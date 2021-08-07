#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

/* Math library */
#include "glm-0.9.9.8/glm/glm.hpp"
#include "glm-0.9.9.8/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.9.8/glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Terrain.h"
#include "Camera.h"

int main(void)
{
    float vertices[] = {
        -5.0f, -5.0f, -5.0f,  0.0f, 0.0f,
         5.0f, -5.0f, -5.0f,  1.0f, 0.0f,
         5.0f,  5.0f, -5.0f,  1.0f, 1.0f,
        -5.0f, -5.0f, -5.0f,  0.0f, 0.0f,
         5.0f,  5.0f, -5.0f,  1.0f, 1.0f,
        -5.0f,  5.0f, -5.0f,  0.0f, 1.0f,
        
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

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1980, 1024, "OpenGL Project", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit(); //initialization GLEW


    /* creating VAO buffer */
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* creating VBO buffer  */
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    Camera camera(window);
    Shader Myshader("C:/ALL_OpenGL/OpenGLSourceFiles/VS_OpenGL_1/OpenGL/OpenGL/VertexShader.txt",
                    "C:/ALL_OpenGL/OpenGLSourceFiles/VS_OpenGL_1/OpenGL/OpenGL/FragmentShader.txt");
    Myshader.use();

    Terrain terrain;
    terrain.terrainInitialization();

    glEnable(GL_DEPTH_TEST);  

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.146f, 0.129f, 0.129f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        camera.use(window);
        glm::mat4 view = camera.getView();
    
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans,  glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(90.0f), 1980.0f/1024.0f, 0.1f, 200.0f);

        glm::mat4 allmatricies = projection * view * trans;
        unsigned int transformLoc = glGetUniformLocation(Myshader.ID, "allmatricies");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(allmatricies));


        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        terrain.terrainDraw();

        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
};