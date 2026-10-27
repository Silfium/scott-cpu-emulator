CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Iinclude/imgui -Iinclude/imgui/backends $(shell pkg-config --cflags glfw3)
LDLIBS = $(shell pkg-config --libs glfw3) -lGL -ldl

IMGUI_SRC = \
    include/imgui/imgui.cpp \
    include/imgui/imgui_draw.cpp \
    include/imgui/imgui_tables.cpp \
    include/imgui/imgui_widgets.cpp \
    include/imgui/backends/imgui_impl_glfw.cpp \
    include/imgui/backends/imgui_impl_opengl3.cpp

SRC = src/main.cpp
TARGET = .build/app

$(TARGET): $(SRC) $(IMGUI_SRC)
	mkdir -p .build
	$(CXX) $(CXXFLAGS) $(SRC) $(IMGUI_SRC) -o $(TARGET) $(LDLIBS)
