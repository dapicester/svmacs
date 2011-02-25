# - Try to find IT
# Once done this will define
#  ITPP_FOUND - System has IT++
#  ITPP_INCLUDE_DIRS - The IT++ include directories
#  ITPP_LIBRARIES - The libraries needed to use IT++
#  ITPP_DEFINITIONS - Compiler switches required for using IT++

find_package(PkgConfig)
pkg_check_modules(PC_ITPP QUIET itpp)
set(ITPP_DEFINITIONS ${PC_ITPP_CFLAGS_OTHERS})

find_path(ITPP_INCLUDE_DIR itpp/itbase.h
          HINTS ${PC_ITPP_INCLUDEDIR} ${PC_ITPP_INCLUDE_DIRS}
          PATH_SUFFIXES itpp )

find_library(ITPP_LIBRARY NAMES itpp libitpp
             HINTS ${PC_ITPP_LIBDIR} ${PC_ITPP_LIBRARY_DIRS} )

set(ITPP_LIBRARIES ${ITPP_LIBRARY} )
set(ITPP_INCLUDE_DIRS ${ITPP_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set ITPP_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(ITPP  DEFAULT_MSG
                                  ITPP_LIBRARY ITPP_INCLUDE_DIR)

mark_as_advanced(ITPP_INCLUDE_DIR ITPP_LIBRARY )
