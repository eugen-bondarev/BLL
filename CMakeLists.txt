cmake_minimum_required(VERSION 3.16)

project(BLL VERSION 1.0.0)

file(GLOB_RECURSE var_src src/*.cpp)

add_executable(BLL ${var_src}) 