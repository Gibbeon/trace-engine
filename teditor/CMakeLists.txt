cmake_minimum_required(VERSION 2.8.9)
project(teditor)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
 
#sample doesn't work without this, we should figure out why
add_compile_options("/sdl")

include_directories(./include)
include_directories(../tengine/include)

link_directories(../tengine/lib)
link_directories(../tewin64/lib)
link_directories(../ted3d12/lib)
 
#this isn't best practice
file(GLOB_RECURSE SOURCES "src/*.cpp" )
add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME} d3d12.lib)
target_link_libraries(${PROJECT_NAME} dxgi.lib)
target_link_libraries(${PROJECT_NAME} D3DCompiler.lib)

target_link_libraries(${PROJECT_NAME} tengine.lib)
target_link_libraries(${PROJECT_NAME} tewin64.lib)
target_link_libraries(${PROJECT_NAME} ted3d12.lib)