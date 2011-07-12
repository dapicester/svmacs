# - Try to find CppUnit
# Once done this will define
#  CPPUNIT_FOUND - System has CppUnit
#  CPPUNIT_INCLUDE_DIRS - The CppUnit include directories
#  CPPUNIT_LIBRARIES - The libraries needed to use CppUnit
#  CPPUNIT_DEFINITIONS - Compiler switches required for using CppUnit

find_package(PkgConfig)
pkg_check_modules(PC_CPPUNIT QUIET CPPUNIT)
set(CPPUNIT_DEFINITIONS ${PC_CPPUNIT_CFLAGS_OTHER})

find_path(CPPUNIT_INCLUDE_DIR cppunit/TestCase.h
          HINTS ${PC_CPPUNIT_INCLUDEDIR} ${PC_CPPUNIT_INCLUDE_DIRS}
          PATH_SUFFIXES cppunit )

find_library(CPPUNIT_LIBRARY NAMES cppunit libccpunit
             HINTS ${PC_CPPUNIT_LIBDIR} ${PC_CPPUNIT_LIBRARY_DIRS} )

set(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} )
set(CPPUNIT_INCLUDE_DIRS ${CPPUNIT_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CPPUNIT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CPPUNIT  DEFAULT_MSG
                                  CPPUNIT_LIBRARY CPPUNIT_INCLUDE_DIR)

mark_as_advanced(CPPUNIT_INCLUDE_DIR CPPUNIT_LIBRARY )
