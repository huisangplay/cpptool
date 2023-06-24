cmake_minimum_required(VERSION 3.23)
project(imgui)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_RELEASE  "$ENV{CXXFLAGS} /MD")
SET(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} /MD")
link_directories(${PROJECT_SOURCE_DIR}/libs)
add_executable(${PROJECT_NAME} main.cpp Application.cpp Application.h)

target_link_libraries(${PROJECT_NAME} d3d11.lib)

FILE(GLOB BACKENDS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/backends/*.cpp)
FILE(GLOB IMGUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${BACKENDS_SRC}
        ${IMGUI_SRC}
        )
