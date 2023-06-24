cmake_minimum_required(VERSION 3.25)
project(curltest)
set(CMAKE_CXX_STANDARD 17)

#msvc编译时防止utf8解析成gbk导致页面显示乱码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#libxl
include_directories(${PROJECT_SOURCE_DIR}/third_party/curl/include)
link_directories(${PROJECT_SOURCE_DIR}/third_party/curl/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(curltest main.cpp)

#链接动态库
target_link_libraries(${PROJECT_NAME} libcurl.lib Crypt32.Lib WS2_32.Lib zlib.lib)