#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Camera.h"
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


int WIDTH = 800;
int HEIGHT = 600;
float DELTA = 0;
float LASTFRAME = 0;
glm::vec3 LIGHTPOS(1.2f, 1.0f, 1.2f);
glm::vec3 LIGHTDIR(0.2f, -1.0f, -0.3f);
Camera CAMERA = Camera();
float LASTX, LASTY;
bool FIRSTMOUSE = true;
glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (FIRSTMOUSE) // initially set to true
	{
		LASTX = xpos;
		LASTY = ypos;
		FIRSTMOUSE = false;
	}
	CAMERA.ProcessMouseMovement(xpos - LASTX, LASTY - ypos);
	LASTX = xpos;
	LASTY = ypos;

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		CAMERA.ProcessKeyboard(FORWARD, DELTA);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		CAMERA.ProcessKeyboard(BACKWARD, DELTA);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		CAMERA.ProcessKeyboard(LEFT, DELTA);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		CAMERA.ProcessKeyboard(RIGHT, DELTA);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		CAMERA.ProcessKeyboard(UP, DELTA);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		CAMERA.ProcessKeyboard(DOWN, DELTA);

}
float VERTICES[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};
int scene2()
{
	//init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lighting", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window";
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<<"Glad error";
		return 0;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WIDTH, HEIGHT);

	//inputs
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);

	Shader objectShader("vertexshader2.vs", "fragmentshader2.fs");
	Shader lightShader("lightvertexshader2.vs", "lightfragmentshader2.fs");

	//VAOs
	unsigned int VAO, lightVAO;
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);

	//VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//VAOs init
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//diffuse map
	unsigned int diffuseMap;
	glGenTextures(1, &diffuseMap);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("textures/container2.png",&width,&height,&nrChannels,0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture";
	}
	stbi_image_free(data);

	//specular map
	unsigned int specularMap;
	glGenTextures(1, &specularMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	data = stbi_load("textures/container2_specular.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture";
	}
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		DELTA = currentFrame - LASTFRAME;
		processInput(window);
		glClearColor(0.2, 0.2, 0.2,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		//objects
		objectShader.use();
		objectShader.setVec3("material.ambient", ambientColor);
		objectShader.setVec3("material.diffuse", diffuseColor);
		objectShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		objectShader.setFloat("material.shininess", 32.0f);
		objectShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		objectShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
		objectShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		objectShader.setVec3("light.position", CAMERA.Position);
		objectShader.setVec3("light.direction", CAMERA.Front);
		objectShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5)));
		objectShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5)));
		objectShader.setFloat("light.constant", 1.0f);
		objectShader.setFloat("light.linear", 0.09f);
		objectShader.setFloat("light.quadratic", 0.032f);
		objectShader.setVec3("viewPos", CAMERA.Position);
		objectShader.setInt("material.diffuse", 0);
		objectShader.setInt("material.specular", 1);

		//view
		glm::mat4 view = CAMERA.GetViewMatrix();
		objectShader.setMat("view", view);
		//projection
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		objectShader.setMat("projection", projection);
		glm::mat4 model;
		//model
		for (unsigned int i = 1; i < 10; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20 * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0, 0.3, 0.5));
			objectShader.setMat("model", model);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		//lights
		lightShader.use();
		//model
		model = glm::mat4(1.0);
		model = glm::translate(model, LIGHTPOS);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat("model", model);
		lightShader.setMat("view", view);
		lightShader.setMat("projection", projection);
		lightShader.setVec3("lightColor", lightColor);
		
		glBindVertexArray(lightVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwPollEvents();

		glfwSwapBuffers(window);

	}

	glfwTerminate();

	return 1;
}