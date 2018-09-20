cmake_minimum_required(VERSION 3.12)
project(q1 C)

set(CMAKE_C_STANDARD 99)
add_executable(a1 q1.c)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
target_link_libraries(a1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} m)
