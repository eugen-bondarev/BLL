cmake_minimum_required(VERSION 3.16)

project(BLL VERSION 1.0.1)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(BUILD_UTILS OFF)

add_subdirectory(external/glew)
add_subdirectory(external/glfw)

file(GLOB_RECURSE var_src src/*.cpp external/imgui/*.cpp)

add_executable(BLL ${var_src}) 

add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(BLL glfw libglew_static)

target_include_directories(
    BLL 
    PRIVATE 
        external/glew/include 
        external/glfw/include 
        external/mnist_reader
        external/imgui
) 

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")