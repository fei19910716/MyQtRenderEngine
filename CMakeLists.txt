cmake_minimum_required(VERSION 3.16.5)

set(target CFRenderEngine)

project(${target})

add_subdirectory(vendor)

find_library(OpenGL_LIBRARY OpenGL )
find_library(Cocoa_LIBRARY Cocoa )
find_library(IOKit_LIBRARY IOKit )

add_executable(${target} src/main.cpp)

target_link_libraries(${target} PRIVATE ${OpenGL_LIBRARY} ${Cocoa_LIBRARY} ${IOKit_LIBRARY} libvendor)