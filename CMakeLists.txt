cmake_minimum_required(VERSION 3.10)
project(Graphics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# stb_image is header-only, just need to include its directory
# Download stb_image.h if not present
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/stb_image.h")
    message(STATUS "Downloading stb_image.h...")
    file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
         "${CMAKE_SOURCE_DIR}/stb_image.h")
endif()

add_executable(Graphics main.cpp
    screen.hpp screen.cpp
    shader.hpp shader.cpp
    Logger.hpp Logger.cpp)

target_include_directories(Graphics PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(Graphics
    ${OPENGL_LIBRARIES}
    GLEW::glew
    glfw
)
