#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <bitset>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ui.h"
#include "utils/utils.h"
#include "utils/components.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); } 

char source[1024] = "";


int main() {

	if (!glfwInit()) {
		return -1;
	}
	//setting the glfw window and activating v_sync
	GLFWwindow* window = glfwCreateWindow(1000, 600, "emulator 8-bit build", NULL, NULL);
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

	//adding font
	ImGuiIO& io = ImGui::GetIO();
	ImFont* fontRegular = io.Fonts->AddFontFromFileTTF("docs/fonts/LiberationSans-Regular.ttf", 18.0f); //regular
	ImFont* fontBold = io.Fonts->AddFontFromFileTTF("docs/fonts/LiberationSans-Bold.ttf", 18.0f);       //bold

	//set up style
	SetupImGuiStyle();




	//------------------------------------|
	//------------------------------------|
	//Main looop
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//setting up ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//setting up font
		ImGui::PushFont(fontRegular);

		//--------------------------------|
		//--------------------------------|
		//RAM window
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 320, .0f), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(320, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		ImGui::Begin("RAM Viewer", nullptr, ImGuiWindowFlags_NoResize 
						| ImGuiWindowFlags_NoCollapse);
		//RAM table
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
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 320 - 284, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(284, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		ImGui::Begin("REGISTERS", nullptr, ImGuiWindowFlags_NoResize |
						   ImGuiWindowFlags_NoCollapse);
		display_register("R0 ", cpu.general_purpose[0], fontRegular, fontBold, 1);
		display_register("R1 ", cpu.general_purpose[1], fontRegular, fontBold, 2);
		display_register("R2 ", cpu.general_purpose[2], fontRegular, fontBold, 3);
		display_register("R3 ", cpu.general_purpose[3], fontRegular, fontBold, 4);
		display_register("TMP", cpu.tmp, fontRegular, fontBold, 5);
		display_register("ACC", cpu.acc, fontRegular, fontBold, 6);
		display_register("IR ", cpu.ir, fontRegular, fontBold, 7);
		display_register("IAR", cpu.iar, fontRegular, fontBold, 8);
		display_flag_register(9);
		display_register("mar", ram.mar, fontRegular, fontBold, 10);
		ImGui::End();

		//---------------------------------|
		//---------------------------------|
		//IDE window
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - 320 - 284, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		ImGui::Begin("EDITOR", nullptr, ImGuiWindowFlags_NoResize | 
						ImGuiWindowFlags_NoCollapse);
		
		ImGui::Button("run");
		ImGui::InputTextMultiline( "##source", source, IM_ARRAYSIZE(source), ImGui::GetContentRegionAvail());

		ImGui::End();

		ImGui::PopFont();
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
