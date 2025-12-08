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
#include <ew/transform.h>
#include <ew/cameraController.h>
#include <ew/texture.h>

#include "gorp/hierarchyNode.h"
#include "gorp/transform.h"
#include "gorp/htrLoader.h"
#include "gorp/clipCtrl.h"
#include "gorp/kinematics.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
GLFWwindow* initWindow(const char* title, int width, int height);
void drawUI();
void resetCamera(ew::Camera* camera, ew::CameraController* controller);
void processInput(GLFWwindow* window);

//Global state
int screenWidth = 1080;
int screenHeight = 720;
int boneCounter = 0;
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
	ew::Shader boneTest = ew::Shader("assets/boneTest.vert", "assets/boneTest.frag");
	//ew::Model monkeyModel = ew::Model("assets/Suzanne.obj");
	//Transform monkeyTransform;

	ew::Model crayfoish = ew::Model("assets/crayfoish_mesh.fbx");
	NodeTransform t;
	t.local.translate = glm::vec4(0, 0, 0, 1);
	t.local.rotate = glm::vec4(0, 0, 0, 0);
	t.local.scale = glm::vec4(1, 1, 1, 1);
	calcTransformMat(t.local);

	GLuint brickTex = ew::loadTexture("assets/stone_color.jpg");

	camera.position = glm::vec3(0.0f, 0.0f, 5.0f);
	camera.target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera.aspectRatio = (float)screenWidth / screenHeight;
	camera.fov = 60.0f;

	//Node test;
	HierarchyList* list = new HierarchyList;
	HeaderData* data = new HeaderData;
	TestHTRLoader(list, data, "assets/crayfoish_animations.txt");

	//base pose fk
	basePoseCovert(list);
	baseSolveFK(list);
	list->baseUpdateLocalInverse(list);
	list->baseUpdateGlobalInverse(list);

	clipCtrl* ctrl = new clipCtrl;
	std::vector<std::string> clipNames;
	clipNames.push_back("clipAnim1");
	clipNames.push_back("clipAnim2");
	clipNames.push_back("clipAnim3");
	float keyframeDuration = 0.0333333333333; // 1/framerate

	//need to initalize clip controller to keep track of the keyframe and where we are in it
	//once we do that we can use the keyframe were in to find the two poses to interpolate using where in the keyfame we are
	//to do this we would need a pose lerp
	//after we would solve fk on the current pose and that should give us a skeleton with animation
	//skinning needs to happen somewhere in here

	clipCtrlInit(ctrl, "anim1", clipNames, keyframeDuration, Animation::anim1keyframecount, 1);
	


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
		processInput(window);

		//RENDER
		glClearColor(0.6f, 0.8f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glBindTextureUnit(0, brickTex);
		shader.setVec3("uEyePos", camera.position);
		shader.setFloat("uMaterial.Ka", material.Ka);
		shader.setFloat("uMaterial.Kd", material.Kd);
		shader.setFloat("uMaterial.Ks", material.Ks);
		shader.setFloat("uMaterial.Shininess", material.Shininess);

		clipControllerUpdate(ctrl, deltaTime);
		list->poseLerp(ctrl->keyframeIndex, ctrl->keyframeIndex + 1, data->boneCount, ctrl->keyframeParam);
		poseConcat(list);
		poseCovert(list);
		solveFK(list);
		list->updateLocalInverse(list);
		list->updateGlobalInverse(list);
		list->updateObjectBindToCurrent(list);
		//first node and last 14 nodes are trash
		glm::mat4 notTrash[55];
		int k = 1;

		for (int i = 0; i < 55; i++)
		{
			notTrash[i] = list->nodePoseList->objectSpaceBindToCurrent[k].global.transformMat;
		}

		//shader.setMat4("uModel", t.local.transformMat);
		//shader.SetMat4Arr("gBones", notTrash);
		shader.setInt("gDisplayBoneIndex", boneCounter);
		shader.setMat4("uModel", t.local.transformMat);
		shader.setMat4("uViewProjection", camera.projectionMatrix() * camera.viewMatrix());
		crayfoish.draw();

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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		boneCounter = (boneCounter + 1) % 55;
	}
}
