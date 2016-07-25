PROJECT(bdgui-test)

SET(LIST_LIB
  bdgui
  pthread
  m
  ${GDSL_LIBRARY}
  ${CAIRO_LIBRARY}
  ${FREETYPE_LIBRARY}
  ${PIXMAN_LIBRARY}
  png
  rt
)

ADD_EXECUTABLE(display_test
  display_test.c
)

ADD_EXECUTABLE(loop_test
  loop_test.c
)

TARGET_LINK_LIBRARIES (
  display_test
  ${LIST_LIB}
)

TARGET_LINK_LIBRARIES (
  loop_test
  ${LIST_LIB}
)
