cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

PROJECT(bdgui)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -msoft-float")

find_package(gdsl REQUIRED)
find_package(freetype REQUIRED)
find_package(pixman REQUIRED)
find_package(cairo REQUIRED)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/src
  ${GDSL_INCLUDE_DIR}
  ${FREETYPE_INCLUDE_DIR}
  ${PIXMAN_INCLUDE_DIR}
  ${CAIRO_INCLUDE_DIR}
)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)