# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_path(FREETYPE_INCLUDE_DIR ft2build.h
        ${CMAKE_FIND_ROOT_PATH}/include/freetype2/)

find_library(FREETYPE_LIBRARY NAMES freetype libfreetype
        ${CMAKE_FIND_ROOT_PATH}/lib)

set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY} )
set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(freetype  DEFAULT_MSG
                                  FREETYPE_LIBRARY FREETYPE_INCLUDE_DIR)

mark_as_advanced(FREETYPE_INCLUDE_DIR FREETYPE_LIBRARY)