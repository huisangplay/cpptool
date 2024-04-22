cmake_minimum_required(VERSION 3.28)
project(dnf_auto)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_RELEASE  "$ENV{CXXFLAGS} /MD")
SET(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} /MD")
#msvc编译时防止utf8解析成gbk导致页面显示乱码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")


# 设置源文件和目标文件的路径
set(source_file "${CMAKE_SOURCE_DIR}/auto_dnf_config.json")
set(destination_file "${CMAKE_SOURCE_DIR}/build/Release/auto_dnf_config.json")

# 调用 configure_file 命令复制文件
configure_file(${source_file} ${destination_file} COPYONLY)

link_directories(${PROJECT_SOURCE_DIR}/libs)
add_executable(${PROJECT_NAME} main.cpp Application.cpp Application.h
        naima.h
        naima.h
        VirtualAtuoUtil.h
        miusi.h
        jianhun.h
        jianying.h
        kuangzhan.h
        jiandi.h
        lvren.h
        renying.h
        axiuluo.h
        AllRole.h
        naiba.h
        utils/windowsutil.cpp
)

target_link_libraries(${PROJECT_NAME} d3d11.lib)

FILE(GLOB BACKENDS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/backends/*.cpp)
FILE(GLOB IMGUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${BACKENDS_SRC}
        ${IMGUI_SRC}
        )
