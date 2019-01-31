cmake_minimum_required(VERSION 3.0)


project(grdn C)

set (grdn_VERSION_MAJOR 0)
set (grdn_VERSION_MINOR 0)
set (grdn_VERSION_PATCH 1)

set (project_name grdn)

macro(use_c99)
	if (CMAKE_VERSION VERSION_LESS "3.1")
		if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
			set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
		endif ()
	else ()
		set (CMAKE_C_STANDARD 99)
	endif ()
endmacro(use_c99)

use_c99()

option(BuildLibrary "Build the brush library for embedding or linking" ON)
option(BuildTest "BuildTest" OFF)
option(BuildDocumentation "BuildDocumentation" OFF)

if(${BuildTest})
  add_subdirectory("test")
endif()



IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	 SET(OperatingSystem "macos")
	 set(contrib_lib_dir ${CMAKE_SOURCE_DIR}/contrib/platform/darwin)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		SET(OperatingSystem "linux")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(WIN32)
		SET(OperatingSystem "windows")
ENDIF()

file(GLOB_RECURSE sources grdn.c src/*.c src/*.cpp)
# file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/vmap/*.cpp)

add_library(grdn STATIC ${sources})

if(${OperatingSystem} MATCHES "macos")
	find_library(CG_LIB CoreGraphics)
	find_library(CF_LIB CoreFoundation)
	target_link_libraries(${project_name} cairo pixman png ${CG_LIB} ${CF_LIB})
endif()

if(${OperatingSystem} MATCHES "linux")
	target_link_libraries(${project_name} cairo pixman png )
endif()


if(${OperatingSystem} MATCHES "windows")
	target_link_libraries(${project_name} cairo pixman png )
endif()

link_directories(test_grdn PUBLIC ${contrib_lib_dir} /usr/lib/arm-linux-gnueabihf)


target_include_directories (grdn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories (grdn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
target_include_directories (grdn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
target_include_directories (grdn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../)
target_include_directories (grdn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)
