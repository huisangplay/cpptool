cmake_minimum_required(VERSION 3.23)
project(imgui)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_RELEASE  "$ENV{CXXFLAGS} -static")
SET(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} -static")
link_directories(${PROJECT_SOURCE_DIR}/libs)
add_executable(imgui main.cpp
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        utils/stringutil.cpp
        utils/windowsutil.cpp)
target_link_libraries(imgui glfw3dll.lib OpenGL32.Lib)
