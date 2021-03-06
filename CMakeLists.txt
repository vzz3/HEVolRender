# $ cmake -G Xcode ..

#######################################################
# --------------- RELEASE BUILD LINUX! ----------------
# #$cmake --config Release ..
# cmake -DCMAKE_BUILD_TYPE=Release ..
#######################################################

cmake_minimum_required(VERSION 3.10)

# set the project name
project(HEVolRender)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

IF(UNIX AND NOT APPLE)
	set(LINUX TRUE)
ENDIF()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
#set(CMAKE_CXX_EXTENSIONS NO)

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
	#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=westmere")
	# print supported instructions for march: $ echo | clang -E - -march=native -###

	set(CMAKE_CXX_FLAGS  "-Werror=return-type ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()

if(APPLE)
	# allow inline ASM
	#set(CMAKE_CXX_FLAGS  "-DRUNTIME_IL2CPP=1")
ENDIF()

#if(APPLE)
	# https://docs.hunter.sh/en/latest/packages/pkg/Qt.html
	#hunter_add_package(Qt COMPONENTS qtbase)
	#hunter_add_package(Qt COMPONENTS qtwebsockets)
	#hunter_add_package(OpenCV)

#	message(STATUS "Install required components on mac OS:")
#	message(STATUS "	$ sudo port install qt513-qtbase +openssl qt513-qttools")
#elseif(UNIX)
#	message(STATUS "unfortunatly you need to install QT manualy")
	#message(STATUS "	UBUNTU: sudo apt-get install qt5-default libqt5websockets5-dev qtconnectivity5-dev libopencv-dev")
	# QT version of Ubuntu 16.04LTS: 5.5.1+dfsg-16ubuntu7
	# QT version of Ubuntu 18.04LTS: 5.9.5+dfsg-0ubuntu1
#endif()

# Generate XCode schemes
set(CMAKE_XCODE_GENERATE_SCHEME TRUE)

# Organize files in folder for IDEs
#set(USE_FOLDERS TRUE)


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


##########################
# copy required assets
#configure_file(${CMAKE_SOURCE_DIR}/browser.sh ${PROJECT_BINARY_DIR}/browser.sh COPYONLY)

###########################
# config for QT
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/qtbase-everywhere-src-5/lib/cmake/")
set(QTVersion "5.12")
# Find includes in corresponding build directories (only required for cmake version < 3.7)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Whether to handle rcc automatically for Qt targets.
set(CMAKE_AUTORCC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# QT base package
#find_package(Qt5Core ${QTVersion} REQUIRED)
#find_package(Qt5Gui ${QTVersion} REQUIRED)
#find_package(Qt5UiTools ${QTVersion} REQUIRED)
#find_package(Qt5Widgets ${QTVersion} REQUIRED)
#find_package(Qt5OpenGL ${QTVersion})
#find_package(Qt5OpenGLExtensions ${QTVersion})
#find_package(Qt5Network ${QTVersion})
#find_package(Qt5Xml ${QTVersion})
find_package(Qt5 ${QTVersion} COMPONENTS Core Widgets Gui REQUIRED)

# QT additional package
#find_package(Qt5WebSockets ${QTVersion} REQUIRED)
#find_package(Qt5Bluetooth ${QTVersion} REQUIRED)

# ## QT links:
# download: http://download.qt.io/official_releases/qt/5.12/5.12.9/submodules/
# list of examples: https://doc.qt.io/qt-5/qtexamples.html
# used example: $HOME/Downloads/qtbase-everywhere-src-5.12.10/examples/vulkan/hellovulkanwidget
# https://www.qt.io/blog/2018/05/30/vulkan-for-qt-on-macos


# ## vulkan
find_package(Vulkan) # Use FindVulkan module added with CMAKE 3.7
IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS "Vulkan library at \"${Vulkan_LIBRARY}\"")
ENDIF()

# GLM
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/glm/cmake/")
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/glm/cmake/")
find_package(glm REQUIRED PATHS  "${CMAKE_CURRENT_SOURCE_DIR}/external/")
IF (NOT glm_FOUND)
	message(FATAL_ERROR "Could not find GLM library!")
ELSE()
	message(STATUS "GLM included at \"${GLM_INCLUDE_DIRS}\"")
ENDIF()



# ## Shader
# https://stackoverflow.com/questions/13540944/including-glsl-files-in-project-pane-in-a-qtcreator-cmake-project
#qt5_add_resources(SHADER_RSC_ADDED
#    hellovulkanwidget.qrc
#)
# https://stackoverflow.com/questions/60420700/cmake-invocation-of-glslc-with-respect-to-includes-dependencies
function(add_shader TARGET SHADER)
    #find_program(GLSLC glslc PATHS ${CMAKE_CURRENT_SOURCE_DIR}/external/google_shaderc_linux_clang_release/bin)
	find_program(GLSLC glslc)

    set(current-shader-path ${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/${SHADER})
    #set(current-output-path ${CMAKE_BINARY_DIR}/shaders/${SHADER}.spv)
	set(current-output-path ${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER}.spv)

    # Add a custom command to compile GLSL to SPIR-V.
    get_filename_component(current-output-dir ${current-output-path} DIRECTORY)
    file(MAKE_DIRECTORY ${current-output-dir})

    add_custom_command(
		   #COMMENT "Generating shader " ${current-output-path}
           OUTPUT ${current-output-path}
           COMMAND
		   		${GLSLC}
				-MD -MF ${current-output-path}.d
				#--target-env=opengl
				-o ${current-output-path}
				#-mfmt=num
				${current-shader-path}
		   #DEPFILE ${current-output-path}.d
           DEPENDS ${current-shader-path}
           IMPLICIT_DEPENDS CXX ${current-shader-path}
           VERBATIM)

    # Make sure our build depends on this output.
    set_source_files_properties(${current-output-path} PROPERTIES GENERATED TRUE)
    target_sources(${TARGET} PRIVATE ${current-output-path})
endfunction(add_shader)


#include_directories(src)
#file(GLOB_RECURSE SRC_LIST *.c* *.h*)
file(GLOB SRC_FILES
    #"src/*.h"
    #"src/*.cpp"
	#"src/**/*.h"
    #"src/**/*.cpp"
	"src/*.c" 		"src/*.cpp"			"src/*.h"		"src/*.hpp"
	"src/*/*.c" 	"src/*/*.cpp"		"src/*/*.h"		"src/*/*.hpp"
	"src/*/*/*.c"	"src/*/*/*.cpp"		"src/*/*/*.h"	"src/*/*/*.hpp"
)
file(GLOB SRC_MATH_FILES
	"src/math/*.c" 		"src/math/*.cpp"		"src/math/*.h"		"src/math/*.hpp"
	"src/math/*/*.c"	"src/math/*/*.cpp"		"src/math/*/*.h"	"src/math/*/*.hpp"
)
file(GLOB SRC_PAILLIER_FILES
	"src/paillier/*.c" 		"src/paillier/*.cpp"		"src/paillier/*.h"		"src/paillier/*.hpp"
	"src/paillier/*/*.c"	"src/paillier/*/*.cpp"		"src/paillier/*/*.h"	"src/paillier/*/*.hpp"
)
file(GLOB SRC_UTIL_FILES
	"src/util/*.c" 		"src/util/*.cpp"		"src/util/*.h"		"src/util/*.hpp"
	"src/util/*/*.c"	"src/util/*/*.cpp"		"src/util/*/*.h"	"src/util/*/*.hpp"
)

file(GLOB APP_FILES
	"app/*.c" 		"app/*.cpp"			"app/*.h"		"app/*.hpp"
	"app/*/*.c" 	"app/*/*.cpp"		"app/*/*.h"		"app/*/*.hpp"
	"app/*/*/*.c"	"app/*/*/*.cpp"		"app/*/*/*.h"	"app/*/*/*.hpp"
)

file(GLOB SHADER_FILES
	"res/shaders/*.vert" 		"res/shaders/*.frag"		"res/shaders/*.glsl"
	"res/shaders/*/*.vert" 		"res/shaders/*/*.frag"		"res/shaders/*/*.glsl"
	"res/shaders/*/*/*.vert"	"res/shaders/*/*/*.frag"	"res/shaders/*/*/*.glsl"
)

file(GLOB TEST_FILES
	"test/*.c" 		"test/*.cpp"		"test/*.h"		"test/*.hpp"
	"test/*/*.c" 	"test/*/*.cpp"		"test/*/*.h"	"test/*/*.hpp"
	"test/*/*/*.c"	"test/*/*/*.cpp"	"test/*/*/*.h"	"test/*/*/*.hpp"
)



# configure the final app target
add_executable(${PROJECT_NAME} ${SRC_FILES}
	${SHADER_FILES}
	${APP_FILES}
	#"${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp"
	#"${CMAKE_CURRENT_SOURCE_DIR}/app/hellovulkanwidget.cpp"
	#"${CMAKE_CURRENT_SOURCE_DIR}/app/trianglerenderer.cpp"
	#"${CMAKE_CURRENT_SOURCE_DIR}/app/hellovulkanwidget.qrc"

	#${SHADER_RSC_ADDED}
)
#add_framework(Security ppvr)

target_link_libraries(${PROJECT_NAME}
	Qt5::Core
	Qt5::Widgets
	Qt5::Gui
)

target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})
IF(APPLE)
	target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARY} "-framework AppKit" "-framework QuartzCore")
ENDIF()
target_compile_definitions(${PROJECT_NAME} PRIVATE MVK_LOG_LEVEL_INFO=1)

add_shader(${PROJECT_NAME} "color.frag")
add_shader(${PROJECT_NAME} "color.vert")
add_shader(${PROJECT_NAME} "axis.frag")
add_shader(${PROJECT_NAME} "axis.vert")
add_shader(${PROJECT_NAME} "cube.frag")
add_shader(${PROJECT_NAME} "cube.vert")
add_shader(${PROJECT_NAME} "quad.frag")
add_shader(${PROJECT_NAME} "quad.vert")
add_shader(${PROJECT_NAME} "xRay.frag")
add_shader(${PROJECT_NAME} "xRay.vert")
add_shader(${PROJECT_NAME} "bigIntTest.frag")
add_shader(${PROJECT_NAME} "bigIntTest.vert")
add_shader(${PROJECT_NAME} "encryptedXRay.frag")
add_shader(${PROJECT_NAME} "encryptedXRay.vert")

configure_file(app/vk_layer_settings.txt vk_layer_settings.txt COPYONLY)

# configuret the test target
add_executable(${PROJECT_NAME}-test ${TEST_FILES} ${SRC_MATH_FILES} ${SRC_PAILLIER_FILES} ${SRC_UTIL_FILES})
#add_framework(Security ppvr-test)
target_link_libraries(${PROJECT_NAME}-test
	Qt5::Core
) # QT core is required in for math/Random thread syncronization

# Set sheme working directory for Xcode (important, because otherwise the compiled shaders can not be found at application startup)
set(CMAKE_XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# for Xcode file tree
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/app" PREFIX "app" FILES ${APP_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/test" PREFIX "test" FILES ${TEST_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "src" FILES ${SRC_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/res/shaders" PREFIX "shaders" FILES ${SHADER_FILES})
