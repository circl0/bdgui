# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_path(PIXMAN_INCLUDE_DIR gdsl.h
        ${CMAKE_FIND_ROOT_PATH}/include)

find_library(PIXMAN_LIBRARY NAMES pixman-1
        ${CMAKE_FIND_ROOT_PATH}/lib)

set(PIXMAN_LIBRARIES ${PIXMAN_LIBRARY} )
set(PIXMAN_INCLUDE_DIRS ${PIXMAN_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(pixman  DEFAULT_MSG
                                  PIXMAN_LIBRARY PIXMAN_INCLUDE_DIR)

mark_as_advanced(PIXMAN_INCLUDE_DIR PIXMAN_LIBRARY )