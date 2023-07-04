cmake_minimum_required(VERSION 3.25)
project(drogon-convertPdf)
SET(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MT")
set(CMAKE_CXX_STANDARD 17)

#msvc编译时防止utf8解析成gbk导致页面显示乱码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

SET(CMAKE_CXX_FLAGS_RELEASE  "$ENV{CXXFLAGS} /MT")

#drogon头文件和lib位置
include_directories(${PROJECT_SOURCE_DIR}/third_party/drogon/include)
link_directories(${PROJECT_SOURCE_DIR}/third_party/drogon/lib)

link_directories(${PROJECT_SOURCE_DIR}/lib)
#jsoncpp头文件和lib位置
include_directories(${PROJECT_SOURCE_DIR}/third_party/jsoncpp/include)
link_directories(${PROJECT_SOURCE_DIR}/third_party/jsoncpp/lib)

add_executable(${PROJECT_NAME} main.cpp utils/DocToUtil.cpp utils/DocToUtil.h utils/DocToUtil.h constants/FileConstant.h constants/PdfConverConstant.h)

#链接动态库
target_link_libraries(${PROJECT_NAME} drogon.lib trantor.lib jsoncpp.lib zlib.lib RpcRT4.Lib WS2_32.Lib)

#复制dev_views下的文件复制到views中，方便开发
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dev_views/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/views/)

#动态编译csp视图
FILE(GLOB_RECURSE CSP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/views/*.csp)
foreach(cspFile ${CSP_LIST})
    string(FIND ${cspFile} "/" pos REVERSE)
    string(SUBSTRING ${cspFile} 0 ${pos} dir)
    execute_process(COMMAND drogon_ctl create view ${cspFile} -o ${dir}/)
endforeach()

#添加src文件
FILE(GLOB_RECURSE CONTROLLER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cc)
FILE(GLOB VIEWSRC ${CMAKE_CURRENT_SOURCE_DIR}/views/*.cc)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${CONTROLLER_LIST}
        ${VIEWSRC}
        )


