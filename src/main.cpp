#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <bitset>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "utils/utils.h"
#include "utils/components.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); } 

//uint8_t ram[256] = {};

void display_register(std::string regName);

int main() {
	
	if (!glfwInit()) {
		return -1;
	}

	//setting the glfw window and activating v_sync
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "emulator 8-bit build", NULL, NULL);
	if (!window) {glfwTerminate(); return -1;}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	//setting the glViewport properly
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
		ImGui::Text("%s", std::bitset<8>(100).to_string().c_str());
		ImGui::End();


		//--------------------------------|
		//--------------------------------|
		//RAM window
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 320, .0f), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(320, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		ImGui::Begin("RAM Viewer", nullptr, ImGuiWindowFlags_NoResize 
						| ImGuiWindowFlags_NoCollapse);
		//RAM table
		ImGui::SetWindowFontScale(1.2f);
		ImGui::BeginTable("RAM display table", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg); {
			ImGui::TableSetupColumn("Addr");
			for (int col = 0; col < 4; col++)
            			ImGui::TableSetupColumn(nullptr);
			
			ImGui::TableHeadersRow();

        		for (int row = 0; row < 32; row++)
        		{	
            			ImGui::TableNextRow();
            			ImGui::TableNextColumn();
            			ImGui::Text("0x%02X", row * 4);

            			for (int col = 0; col < 4; col++) {
                			ImGui::TableNextColumn();
                			ImGui::Text("%02X", ram.ram256[row * 4 + col]);
            			}
        		}
			ImGui::EndTable();
		}
		ImGui::End();

		//---------------------------------|
		//---------------------------------|
		//registers window Window
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 320 - 384, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(384, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		ImGui::Begin("Registers", nullptr, ImGuiWindowFlags_NoResize |
						   ImGuiWindowFlags_NoCollapse);
		ImGui::SetWindowFontScale(1.2f);


		ImGui::End();	


		//---------------------------------|
		//---------------------------------|
		//Registers window
	
		//rendering 
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

void display_register(std::string regName) {
	
}
