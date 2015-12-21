# - Locate XERCESC library
# Defines:
#
#  XERCESC_FOUND
#  XERCESC_INCLUDE_DIR
#  XERCESC_INCLUDE_DIRS (not cached)
#  XERCESC_LIBRARY
#  XERCESC_LIBRARIES (not cached)


if(NOT XERCESC_FOUND)

  find_path(XERCESC_INCLUDE_DIR xercesc/util/XercesVersion.hpp
            HINTS ENV XERCESC_ROOT_DIR
            PATH_SUFFIXES include)
  
  find_library(XERCESC_LIBRARY xerces-c
               HINTS ENV XERCESC_ROOT_DIR
               PATH_SUFFIXES lib)


  set(XERCESC_LIBRARIES ${XERCESC_LIBRARY})
  set(XERCESC_INCLUDE_DIRS ${XERCESC_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set CCFITS_FOUND to TRUE if
# all listed variables are TRUE
  INCLUDE(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(XERCESC DEFAULT_MSG XERCESC_INCLUDE_DIRS XERCESC_LIBRARIES)

  mark_as_advanced(XERCESC_FOUND XERCESC_INCLUDE_DIRS XERCESC_LIBRARIES)

  list(REMOVE_DUPLICATES XERCESC_LIBRARIES)
  list(REMOVE_DUPLICATES XERCESC_INCLUDE_DIRS)

endif()
