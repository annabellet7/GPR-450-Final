#pragma once
#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ew/shader.h>
#include <ew/model.h>
#include <ew/camera.h>
//#include <ew/transform.h>
#include <ew/cameraController.h>
#include <ew/texture.h>

#include "gorp/hierarchyNode.h"
#include "gorp/transform.h"
#include "gorp/htrLoader.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
GLFWwindow* initWindow(const char* title, int width, int height);
void drawUI();
void resetCamera(ew::Camera* camera, ew::CameraController* controller);

//Global state
int screenWidth = 1080;
int screenHeight = 720;
float prevFrameTime;
float deltaTime;
ew::Camera camera;
ew::CameraController cameraController;

struct Material {
	float Ka = 1.0;
	float Kd = 0.5;
	float Ks = 0.5;
	float Shininess = 128;
}material;



int main() {
	GLFWwindow* window = initWindow("GPR-450 Final", screenWidth, screenHeight);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	ew::Shader shader = ew::Shader("assets/lit.vert", "assets/lit.frag");
	ew::Model monkeyModel = ew::Model("assets/Suzanne.obj");
	Transform monkeyTransform;

	GLuint brickTex = ew::loadTexture("assets/stone_color.jpg");

	camera.position = glm::vec3(0.0f, 0.0f, 5.0f);
	camera.target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera.aspectRatio = (float)screenWidth / screenHeight;
	camera.fov = 60.0f;

	//Node test;
	HierarchyList* listTest = new HierarchyList;
	HeaderData* data = new HeaderData;
	TestHTRLoader(listTest, data, "assets/crayfoish_animations.txt");

	//fk stuff
	//nodeTransforms headTransform;
	//headTransform.local.translate = glm::vec4(0, 0, 0, 1);
	//headTransform.local.rotate = glm::vec4(0, 90, 0, 0);
	//headTransform.local.scale = glm::vec4(1, 1, 1, 1);

	//nodeTransforms childTransform;
	//childTransform.local.translate = glm::vec4(1, 0, 0, 1);
	//childTransform.local.rotate = glm::vec4(0, 0, 0, 0);
	//childTransform.local.scale = glm::vec4(1, 1, 1, 1);

	/*HierarchyNode root;
	root.name = "rootNode";
	root.selfIndex = 0;
	root.parentIndex = -1;

	HierarchyNode leaf;
	leaf.name = "rootNode";
	leaf.selfIndex = 1;
	leaf.parentIndex = 0;

	std::vector<HierarchyNode> hierarchy;
	std::vector<nodeTransforms> transformList;

	hierarchy.push_back(root);
	hierarchy.push_back(leaf);

	transformList.push_back(headTransform);
	transformList.push_back(childTransform);*/

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		float time = (float)glfwGetTime();
		deltaTime = time - prevFrameTime;
		prevFrameTime = time;

		//RENDER
		glClearColor(0.6f,0.8f,0.92f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glBindTextureUnit(0, brickTex);
		shader.setVec3("uEyePos", camera.position);
		shader.setFloat("uMaterial.Ka", material.Ka);
		shader.setFloat("uMaterial.Kd", material.Kd);
		shader.setFloat("uMaterial.Ks", material.Ks);
		shader.setFloat("uMaterial.Shininess", material.Shininess);

		//calcTransformMat(&headTransform.global);
		//headTransform.global.transformMat = glm::translate(headTransform.global.transformMat, headTransform.global.translate);
		//monkeyTransform.rotation = glm::rotate(monkeyTransform.rotation, deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		/*calcTransformMat(&headTransform.local);
		shader.setMat4("uModel", headTransform.local.transformMat);
		shader.setMat4("uViewProjection", camera.projectionMatrix() * camera.viewMatrix());

		monkeyModel.draw();

		FKSolver(transformList, hierarchy);

		calcTransformMat(&childTransform.local);
		shader.setMat4("uModel", childTransform.local.transformMat);
		shader.setMat4("uViewProjection", camera.projectionMatrix() * camera.viewMatrix());

		monkeyModel.draw();*/

		//headTransform.local.rotate = headTransform.local.rotate + glm::vec4(0, 1, 0, 0);
		//calcTransformMat(&headTransform.local);
		
		

		cameraController.move(window, &camera, deltaTime);

		drawUI();

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

void drawUI() {
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");

	if (ImGui::CollapsingHeader("Material")) {
		ImGui::SliderFloat("AmbientK", &material.Ka, 0.0f, 1.0f);
		ImGui::SliderFloat("DiffuseK", &material.Kd, 0.0f, 1.0f);
		ImGui::SliderFloat("SpecularK", &material.Ks, 0.0f, 1.0f);
		ImGui::SliderFloat("Shininess", &material.Shininess, 2.0f, 1024.0f);
	}

	if (ImGui::Button("Reset Camera"))
	{
		resetCamera(&camera, &cameraController);
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;
	camera.aspectRatio = (float)width / height;
}

/// <summary>
/// Initializes GLFW, GLAD, and IMGUI
/// </summary>
/// <param name="title">Window title</param>
/// <param name="width">Window width</param>
/// <param name="height">Window height</param>
/// <returns>Returns window handle on success or null on fail</returns>
GLFWwindow* initWindow(const char* title, int width, int height) {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return nullptr;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	return window;
}

void resetCamera(ew::Camera* camera, ew::CameraController* controller)
{
	camera->position = glm::vec3(0.0f, 0.0f, 5.0f);
	camera->target = glm::vec3(0.0f);
	controller->yaw = 0.0f;
	controller->pitch = 0.0f;
}