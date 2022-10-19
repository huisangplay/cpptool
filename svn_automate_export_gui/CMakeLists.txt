cmake_minimum_required(VERSION 3.23)
project(imgui)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_RELEASE  "$ENV{CXXFLAGS} /MD")
SET(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} /MD")
link_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/ftpclient/include)
add_executable(imgui main.cpp
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        utils/stringutil.cpp
        utils/windowsutil.cpp
        utils/json.hpp
        idealsvnexport.cpp
        cpcsvnexport.cpp
        utils/CurlHandle.cpp
        utils/FTPClient.cpp
        )
target_link_libraries(imgui glfw3dll.lib OpenGL32.Lib libcurl.lib)
