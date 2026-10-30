#include <iostream>
#include <GLFW/glfw3.h>
#include <bitset>


#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); } 

uint8_t ram[256] = {};

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
		ImGui::Text("%s", std::bitset<8>(100).to_string().c_str());
		ImGui::End();


		//--------------------------------|
		//--------------------------------|
		//RAM window
		ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(500, ImGui::GetIO().DisplaySize.y - 200), ImGuiCond_Always);
		ImGui::Begin("RAM Viewer", nullptr, ImGuiWindowFlags_NoResize 
						| ImGuiWindowFlags_NoCollapse);

		//RAM table
		ImGui::SetWindowFontScale(1.2f);
		ImGui::BeginTable("RAM display table", 9, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg); {
			ImGui::TableSetupColumn("Addr");
			for (int col = 0; col < 8; col++)
            			ImGui::TableSetupColumn(nullptr);
			
			ImGui::TableHeadersRow();

        		for (int row = 0; row < 16; row++)
        		{	
            			ImGui::TableNextRow();
            			ImGui::TableNextColumn();
            			ImGui::Text("0x%02X", row * 16);

            			for (int col = 0; col < 8; col++) {
                			ImGui::TableNextColumn();
                			ImGui::Text("%02X", ram[row * 8 + col]);
            			}
        		}
			ImGui::EndTable();		
		}
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
