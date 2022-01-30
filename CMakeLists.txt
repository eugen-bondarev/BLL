cmake_minimum_required(VERSION 3.16)

project(BLL VERSION 1.0.1)

include(external/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE var_src src/*.cpp external/imgui/*.cpp)

add_executable(BLL ${var_src}) 

add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(BLL PRIVATE glfw GLEW::GLEW imgui::imgui)
target_include_directories(BLL PRIVATE external/mnist_reader)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")