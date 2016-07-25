# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_path(CAIRO_INCLUDE_DIR cairo.h
        ${CMAKE_FIND_ROOT_PATH}/include/cairo/)

find_library(CAIRO_LIBRARY NAMES cairo
        ${CMAKE_FIND_ROOT_PATH}/lib)

set(CAIRO_LIBRARIES ${CAIRO_LIBRARY} )
set(CAIRO_INCLUDE_DIRS ${CAIRO_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(cairo  DEFAULT_MSG
                                  CAIRO_LIBRARY CAIRO_INCLUDE_DIR)

mark_as_advanced(CAIRO_INCLUDE_DIR CAIRO_LIBRARY)