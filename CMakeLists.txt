cmake_minimum_required(VERSION 3.22)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_executable(OpenGL main.cpp)


target_link_libraries(${PROJECT_NAME} opengl32)
