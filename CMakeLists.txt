# cmake -G Xcode ..

cmake_minimum_required(VERSION 3.10)

# set the project name
project(ppvr_vulkan)

macro(ADD_FRAMEWORK fwname appname)
    find_library(FRAMEWORK_${fwname}
	    NAMES ${fwname}
	    PATHS ${CMAKE_OSX_SYSROOT}/System/Library
	    PATH_SUFFIXES Frameworks
	    NO_DEFAULT_PATH
	)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        # TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}")
		TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}")
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(ADD_FRAMEWORK)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_CXX_FLAGS  "-Werror=return-type ${GCC_COVERAGE_COMPILE_FLAGS}")

#include_directories(src)
#file(GLOB_RECURSE SRC_LIST *.c* *.h*)
file(GLOB SRC_FILES
    #"src/*.h"
    #"src/*.cpp"
	#"src/**/*.h"
    #"src/**/*.cpp"
	"src/*"
	"src/*/*"
	"src/*/*/*"
)

file(GLOB TEST_FILES
	"test/*"
	"test/*/*"
	"test/*/*/*"
)

# add the executable
add_executable(ppvr ${SRC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp")
add_framework(Security ppvr)

add_executable(ppvr-test ${SRC_FILES} ${TEST_FILES})
add_framework(Security ppvr-test)

# for Xcode file tree
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "src" FILES ${SRC_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/test" PREFIX "test" FILES ${TEST_FILES})
