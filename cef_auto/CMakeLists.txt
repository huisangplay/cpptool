cmake_minimum_required(VERSION 3.25)
project(cef_auto)
SET(CMAKE_BUILD_TYPE"RELEASE")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 17)

#msvc编译时防止utf8解析成gbk导致页面显示乱码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#CEF头文件和lib位置
include_directories(${PROJECT_SOURCE_DIR}/third_party/CEF)
link_directories(${PROJECT_SOURCE_DIR}/third_party/CEF/lib)

add_executable(${PROJECT_NAME} WIN32 main.cpp)

#链接动态库
target_link_libraries(${PROJECT_NAME} libcef_dll_wrapper.lib libcef.lib)

FILE(GLOB ROOTSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${ROOTSRC}
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND mt.exe -manifest ${CMAKE_CURRENT_SOURCE_DIR}/cefclient.exe.manifest -outputresource:${CMAKE_CURRENT_BINARY_DIR}/Release/${PROJECT_NAME}.exe)