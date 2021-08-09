#pragma once
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

/* Math library */
#include "glm-0.9.9.8/glm/glm.hpp"
#include "glm-0.9.9.8/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.9.8/glm/gtc/type_ptr.hpp"


class Camera
{
private:
	float deltaTime = 0.0f;	
	float lastFrame = 0.0f;
	void processInput(GLFWwindow* window);
	glm::mat4 view;
public:
	Camera(GLFWwindow* window)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	void use(GLFWwindow* window);
	glm::mat4 getView();

   
};


