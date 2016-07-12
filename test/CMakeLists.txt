PROJECT(bdgui-test)

SET(LIST_LIB
  bdgui
  pthread
  ${GDSL_LIBRARY}
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