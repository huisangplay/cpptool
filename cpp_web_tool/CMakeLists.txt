cmake_minimum_required(VERSION 3.5.0)
project(cpp_web_tool VERSION 0.1.0 LANGUAGES C CXX)

add_executable(cpp_web_tool main.cpp)

target_link_libraries(cpp_web_tool ws2_32)