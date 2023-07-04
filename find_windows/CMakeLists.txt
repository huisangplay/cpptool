cmake_minimum_required(VERSION 3.25)
project(find_windows)

set(CMAKE_CXX_STANDARD 17)
link_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(find_windows main.cpp)

target_link_libraries(find_windows dwmapi.lib)
