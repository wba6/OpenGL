cmake_minimum_required(VERSION 3.22)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/vender/glfw/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glad)

add_executable(OpenGL src/main.cpp src/glfwWindow.cpp src/glfwWindow.h src/Core_defines.h src/shader.cpp src/shader.h src/vender/stb_image.h src/vender/stb_image.cpp)



target_link_libraries(${PROJECT_NAME} opengl32 glfw ${GLFW_LIBRARIES} glad)
