cmake_minimum_required(VERSION 2.8)

PROJECT(cs480)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules/)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Assimp REQUIRED)

INCLUDE_DIRECTORIES(
  include/engine
  include/
  /usr/include/bullet/
  /usr/include/glm/
  ${GLEW_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${ASSIMP_INCLUDE_DIRS}
)
SET(gl_SOURCE
  ${PROJECT_SOURCE_DIR}/src/engine/abstractscene.cpp
  ${PROJECT_SOURCE_DIR}/src/engine/baseglscene.cpp
  ${PROJECT_SOURCE_DIR}/src/engine/glapplication.cpp
)

ADD_SUBDIRECTORY(src)
