# - Try to find RLog
# Once done this will define
#  RLOG_FOUND - System has RLog
#  RLOG_INCLUDE_DIRS - The RLog include directories
#  RLOG_LIBRARIES - The libraries needed to use RLog
#  RLOG_DEFINITIONS - Compiler switches required for using RLog

find_package(PkgConfig)
pkg_check_modules(PC_RLOG QUIET rlog)
set(RLOG_DEFINITIONS ${PC_RLOG_CFLAGS_OTHER})

find_path(RLOG_INCLUDE_DIR rlog/rlog.h
          HINTS ${PC_RLOG_INCLUDEDIR} ${PC_RLOG_INCLUDE_DIRS}
          PATH_SUFFIXES rlog )

find_library(RLOG_LIBRARY NAMES rlog librlog
             HINTS ${PC_RLOG_LIBDIR} ${PC_RLOG_LIBRARY_DIRS} )

set(RLOG_LIBRARIES ${RLOG_LIBRARY} )
set(RLOG_INCLUDE_DIRS ${RLOG_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set RLOG_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(RLog  DEFAULT_MSG
                                  RLOG_LIBRARY RLOG_INCLUDE_DIR)

mark_as_advanced(RLOG_INCLUDE_DIR RLOG_LIBRARY )
