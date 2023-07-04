cmake_minimum_required(VERSION 3.25)
project(httplib_convertpdf)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#sqlite3
include_directories(${PROJECT_SOURCE_DIR}/sqlite3/include)
link_directories(${PROJECT_SOURCE_DIR}/sqlite3/lib)

link_directories(${PROJECT_SOURCE_DIR}/libs)

add_executable(httplib_convertpdf main.cpp DocToUtil.cpp StringUtil.cpp)

target_link_libraries(${PROJECT_NAME} RpcRT4.Lib sqlite3.lib)