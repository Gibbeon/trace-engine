cmake_minimum_required(VERSION 2.8.9)
project(tecore)

set (PROJECTNAME_ARCHITECTURE "x64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
 
add_compile_options("/sdl")
include_directories(../include)
 
add_executable(tecore WIN32 src/main.cpp src/window.cpp src/win32application.cpp)

target_link_libraries(${PROJECT_NAME} d3d12.lib)
target_link_libraries(${PROJECT_NAME} dxgi.lib)