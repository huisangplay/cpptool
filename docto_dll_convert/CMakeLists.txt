cmake_minimum_required(VERSION 3.25)
project(docto)

set(CMAKE_CXX_STANDARD 17)
#msvc编译时防止utf8解析成gbk导致页面显示乱码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_executable(docto main.cpp)

FILE(GLOB DOCHPPSRC${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${DOCHPPSRC}
        )
