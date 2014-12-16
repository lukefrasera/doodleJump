cmake_minimum_required(VERSION 2.8)

PROJECT(cs480)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules/)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

INCLUDE_DIRECTORIES(
  include/engine
  include/
  /usr/include/bullet/
  ${GLEW_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
)
SET(gl_SOURCE
  ${PROJECT_SOURCE_DIR}/src/engine/abstractscene.cpp
  ${PROJECT_SOURCE_DIR}/src/engine/baseglscene.cpp
  ${PROJECT_SOURCE_DIR}/src/engine/glapplication.cpp
)

ADD_SUBDIRECTORY(src)