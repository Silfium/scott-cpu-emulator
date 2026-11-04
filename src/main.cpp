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

void display_register(std::string regName, Reg reg, ImFont* regular, ImFont* bold, int buttonID);

void SetupImGuiStyle();

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


	//adding font
	ImGuiIO& io = ImGui::GetIO();
	ImFont* fontRegular = io.Fonts->AddFontFromFileTTF("docs/fonts/LiberationSans-Regular.ttf", 18.0f); //regular
	ImFont* fontBold = io.Fonts->AddFontFromFileTTF("docs/fonts/LiberationSans-Bold.ttf", 18.0f);       //bold

	//set up style
	SetupImGuiStyle();


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
		ImGui::Begin("Registers", nullptr, ImGuiWindowFlags_NoResize |
						   ImGuiWindowFlags_NoCollapse);
		display_register("R0 ", cpu.general_purpose[0], fontRegular, fontBold, 1);
		display_register("R1 ", cpu.general_purpose[1], fontRegular, fontBold, 2);
		display_register("R2 ", cpu.general_purpose[2], fontRegular, fontBold, 3);
		display_register("R3 ", cpu.general_purpose[3], fontRegular, fontBold, 4);
		display_register("TMP", cpu.tmp, fontRegular, fontBold, 5);
		display_register("ACC", cpu.acc, fontRegular, fontBold, 6);
		display_register("IR ", cpu.ir, fontRegular, fontBold, 7);
		display_register("IAR", cpu.iar, fontRegular, fontBold, 8);

		ImGui::End();


		//---------------------------------|
		//---------------------------------|
		//Registers window
		

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

void display_register(std::string regName, Reg reg, ImFont* regular, ImFont* bold, int buttonID) {
	
	ImGui::PushID(buttonID);

	ImGui::Dummy(ImVec2(0.0f, 3.0f));
	ImGui::PushFont(regular);
	ImGui::SetWindowFontScale(1.2f);

	ImGui::Text("%s", regName.c_str());
	ImGui::SetWindowFontScale(1.0f);

	ImGui::PopFont();
	ImGui::SameLine();

	ImGui::PushFont(regular);
	ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0, 0, 0, 255));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.5f);

	
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 225.0f);
	//ImGui::SeparatorEX(ImGuiSeparatorFlags_Vertical);
	ImGui::Button(print_binary(reg.value).c_str(), ImVec2(96, 28)); 
	ImGui::SameLine();
	ImGui::Button("0xFF", ImVec2(56, 28));
	ImGui::SameLine();
	ImGui::Button("255", ImVec2(48, 28));
	ImGui::Dummy(ImVec2(0.0f, 3.0f));
	ImGui::Separator();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(3);

	ImGui::PopFont();

	ImGui::PopID();
}




void SetupImGuiStyle()
{
	// Classic Steam style by metasprite from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();
	
	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	//style.TabRounding = 0.0f;
	//style.TabBorderSize = 0.0f;
	//style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
	
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.49803922f, 0.49803922f, 0.49803922f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.13725491f, 0.15686275f, 0.10980392f, 0.52f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26666668f, 0.29803923f, 0.22745098f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.29803923f, 0.3372549f, 0.25882354f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.2784314f, 0.31764707f, 0.23921569f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24705882f, 0.29803923f, 0.21960784f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.22745098f, 0.26666668f, 0.20784314f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 0.4f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 0.6f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.13725491f, 0.15686275f, 0.10980392f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1882353f, 0.22745098f, 0.1764706f, 0.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
	//style.Colors[ImGuiCol_Tab] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
	//style.Colors[ImGuiCol_TabHovered] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.78f);
	//style.Colors[ImGuiCol_TabActive] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
	//style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
	//style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.60784316f, 0.60784316f, 0.60784316f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.7764706f, 0.2784314f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882353f, 0.1882353f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.30980393f, 0.30980393f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.22745098f, 0.22745098f, 0.24705882f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.7294118f, 0.6666667f, 0.23921569f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}
