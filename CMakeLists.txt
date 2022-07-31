cmake_minimum_required(VERSION 3.22)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/vender/glfw/include"
        "${PROJECT_SOURCE_DIR}/vender/glm/glm"
        " ${PROJECT_SOURCE_DIR}/vender/glad/include"
        " ${PROJECT_SOURCE_DIR}/vender/"
        )

add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glfw)
add_compile_definitions(GLFW_INCLUDE_NONE)
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glm)

add_executable(OpenGL src/main.cpp src/glfwWindow.cpp src/glfwWindow.h src/Core_defines.h src/shader.cpp src/shader.h
        vender/stb/stb_image.h vender/stb/stb_image.cpp src/texture.cpp src/texture.h vender/glad/include/glad/glad.h
        vender/glad/src/glad.c)


target_link_libraries(${PROJECT_NAME} glfw glm)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/shaders ${PROJECT_SOURCE_DIR}/cmake-build-debug/shaders
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/textures ${PROJECT_SOURCE_DIR}/cmake-build-debug/textures
        )