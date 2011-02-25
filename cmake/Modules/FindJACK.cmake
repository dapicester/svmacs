# - Try to find JACK
# Once done this will define
#  JACK_FOUND - System has JACK
#  JACK_INCLUDE_DIRS - The JACK include directories
#  JACK_LIBRARIES - The libraries needed to use JACK
#  JACK_DEFINITIONS - Compiler switches required for using JACK

find_package(PkgConfig)
pkg_check_modules(PC_JACK QUIET jack)
set(JACK_DEFINITIONS ${PC_JACK_CFLAGS_OTHER})

find_path(JACK_INCLUDE_DIR jack/jack.h
          HINTS ${PC_JACK_INCLUDEDIR} ${PC_JACK_INCLUDE_DIRS}
          PATH_SUFFIXES jack )

find_library(JACK_LIBRARY NAMES jack libjack jackd libjackd
             HINTS ${PC_JACK_LIBDIR} ${PC_JACK_LIBRARY_DIRS} )

set(JACK_LIBRARIES ${JACK_LIBRARY} )
set(JACK_INCLUDE_DIRS ${JACK_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set JACK_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(JACK  DEFAULT_MSG
                                  JACK_LIBRARY JACK_INCLUDE_DIR)

mark_as_advanced(JACK_INCLUDE_DIR JACK_LIBRARY )
