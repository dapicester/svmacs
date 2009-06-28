# compiler flags
include(${CMAKE_ROOT}/Modules/FindQt4.cmake)
include(${QT_USE_FILE})
include_directories(/usr/include)
include_directories(. ../lib ./utils)
#add_definitions(-Wall -g -DNDEBUG -O3 -march=pentium4 -pipe)
add_definitions(-Wall -W -g `pkg-config --cflags jack` `itpp-config --cflags`)
add_definitions(-fbounds-check)

# linker options
link_directories(${PROJECT_SOURCE_DIR}/lib)
#link_libraries(jack pthread rt itpp fftw3 lapack blas rlog jackcpp svm)

# headers
set(svmacs_HDRS
	features/processor.h
	features/feature.h
	features/zcr.h
	features/energy.h
	features/ass.h 
	features/srf.h 
	features/hr.h 
	features/mfcc.h
	model/classifier.h
	model/svmclassifier.h
	jack/jackclient.h
	jack/ringbufferread.h
	cli/svmaccli.h
	gui/svmacgui.h
)

# sources
set(svmacs_SRCS
	features/processor.cpp
	features/zcr.cpp
	features/energy.cpp
	features/ass.cpp
	features/srf.cpp 
	features/hr.cpp 
	features/mfcc.cpp
	model/svmclassifier.cpp
	jack/jackclient.cpp
	jack/ringbufferread.cpp
	cli/svmaccli.cpp
	gui/svmacgui.cpp
	main.cpp 
)

### qt4 ui
set(svmacs_UIS gui/svmacgui.ui)
qt4_wrap_ui(svmacs_UIS_H ${svmacs_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

### qt4 moc
set(svmacs_MOCS gui/svmacgui.h)
qt4_wrap_cpp(svmacs_MOCS_SRC ${svmacs_MOCS})

### qt4 resources
set (svmacs_RCCS application.qrc)
qt4_add_resources(svmacs_RCCS_SRC ${svmacs_RCCS})

# executable
add_executable(svmacs ${svmacs_SRCS} ${svmacs_HDRS} ${svmacs_UIS_H} ${svmacs_MOCS_SRC} ${svmacs_RCCS_SRC})
# link
target_link_libraries(svmacs ${QT_LIBRARIES} jack pthread rt itpp fftw3 lapack blas rlog jackcpp svm)
# output dir
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

add_custom_command(
	TARGET svmacs
	POST_BUILD
	COMMAND cp src/model/m1 src/model/model ${BIN_DIR}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMENT "Copying model files"
)

#set(CMAKE_EXE_LINKER_FLAGS "-static")
