

cmake_minimum_required(VERSION 3.10)

# set the project name
project(ppvr_vulkan)

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

add_executable(ppvr-test ${SRC_FILES} ${TEST_FILES})

# for Xcode file tree
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "src" FILES ${SRC_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/test" PREFIX "test" FILES ${TEST_FILES})
