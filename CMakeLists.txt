cmake_minimum_required(VERSION 3.16)

project(BLL VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(external/glew/build/cmake)
add_subdirectory(external/glfw)

file(GLOB_RECURSE var_src src/*.cpp external/imgui/*.cpp)

add_executable(BLL ${var_src}) 

target_link_libraries(BLL glew_s)
target_link_libraries(BLL glfw)

target_include_directories(BLL PRIVATE external/glew/include external/glfw/include external/imgui) 