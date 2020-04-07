cmake_minimum_required(VERSION 3.17)
project(WINDOW)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not fount")
endif(NOT OPENGL_FOUND)

set(GL_LIBRARY GL GLU X11)

add_executable(main main.cpp)

target_link_libraries(main GLEW::GLEW glfw ${GL_LIBRARY} m)
