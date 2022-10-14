cmake_minimum_required(VERSION 3.23)
project(search_string_imgui)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_RELEASE  "$ENV{CXXFLAGS} /MD /CGTHREADS:8 /OPT:REF")
SET(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} /MD /LARGEADDRESSAWARE")
#libxl
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/libxl/include/include_cpp)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/libxl/lib)

#imgui
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/imgui/lib)

#podofo
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/podofo/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/podofo/lib)

#doctotext
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/doctotext/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/doctotext/lib)


add_executable(search_string_imgui
        search.cpp
        utils/search_excel.cpp
        utils/search_text.cpp
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        utils/stringutil.cpp
        utils/windowsutil.cpp
        utils/json.hpp
        search_string_imgui.cpp
        utils/search_pdf.cpp
        utils/search_pdf.cpp
        utils/TextExtractor.cpp
        utils/search_doctotext.cpp
        )
target_link_libraries(search_string_imgui libxl.lib glfw3dll.lib OpenGL32.Lib libpodofo.lib)

