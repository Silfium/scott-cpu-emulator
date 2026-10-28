#include <iostream>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); } 

int main() {
	
	if (!glfwInit()) {
		return -1;
	}

	//setting the glfw window and activating v_sync
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "app", NULL, NULL);
	if (!window) {glfwTerminate(); return -1;}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	//setting the gloViewport properly
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	int screen_height, screen_width;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);


	//setting DearImgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	
	//------------------------------------|
	//Main looop
	while(!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();

		//setting up ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//--------------------------------|
		//first window test
		ImGui::Begin("testing Imgui");
		ImGui::Text("test UI");
		ImGui::End();

		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	//terminate Imgui and glfw
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	std::cout << "test 2\n";
	return 0;
}
