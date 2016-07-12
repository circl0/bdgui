# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_path(GDSL_INCLUDE_DIR gdsl.h
        ${CMAKE_FIND_ROOT_PATH}/include)

find_library(GDSL_LIBRARY NAMES gdsl libgdsl
        ${CMAKE_FIND_ROOT_PATH}/lib)

set(GDSL_LIBRARIES ${GDSL_LIBRARY} )
set(GDSL_INCLUDE_DIRS ${GDSL_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(gdsl  DEFAULT_MSG
                                  GDSL_LIBRARY GDSL_INCLUDE_DIR)

mark_as_advanced(GDSL_INCLUDE_DIR GDSL_LIBRARY )