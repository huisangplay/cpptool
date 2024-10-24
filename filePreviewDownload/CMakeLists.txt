cmake_minimum_required(VERSION 3.29)
project(filePreviewDownload)
set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR}/third_party/miniz/include/miniz)
link_directories(${PROJECT_SOURCE_DIR}/third_party/miniz/lib)
add_executable(filePreviewDownload main.cpp)

target_link_libraries(filePreviewDownload PRIVATE  Ws2_32.lib libminiz)