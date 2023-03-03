cmake_minimum_required(VERSION 3.15)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
if (WIN32)
    include_directories("${PROJECT_SOURCE_DIR}/vender/glfw/include"
            "${PROJECT_SOURCE_DIR}/vender/glm/glm"
            "${PROJECT_SOURCE_DIR}/vender/glm/"
            " ${PROJECT_SOURCE_DIR}/vender/glad/include"
            " ${PROJECT_SOURCE_DIR}/vender/assimp/include"
            " ${PROJECT_SOURCE_DIR}/vender/"
            " ${PROJECT_SOURCE_DIR}/vender/imgui/"
            )
endif ()
if (UNIX)
    include_directories(
            " ${PROJECT_SOURCE_DIR}/vender/"
    )
endif ()
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glfw)
add_compile_definitions(GLFW_INCLUDE_NONE)
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/assimp)
#add_subdirectory(${PROJECT_SOURCE_DIR}/vender/imgui)

add_executable(OpenGL src/main.cpp src/glfwWindow.cpp src/glfwWindow.h src/Common_defines.h src/Shader.cpp src/Shader.h
        vender/stb/stb_image.h vender/stb/stb_image.cpp src/texture.cpp src/texture.h vender/glad/include/glad/glad.h
        vender/glad/src/glad.c src/Camera.cpp src/Camera.h src/ScenePicker.cpp src/ScenePicker.h src/Scene.h src/Scenes/RoomOfBoxes.h src/Scenes/Lighting.h
        src/Scenes/Mesh.cpp
        )


target_link_libraries(${PROJECT_NAME} glfw glm assimp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/shaders ${PROJECT_SOURCE_DIR}/cmake-build-debug/shaders
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/textures ${PROJECT_SOURCE_DIR}/cmake-build-debug/textures
        )