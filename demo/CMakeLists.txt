cmake_minimum_required (VERSION 3.0)

message ("configuring demo.")

project (grdn_demo)

set (grdn_demo_VERSION_MAJOR 0)
set (grdn_demo_VERSION_MINOR 0)
set (grdn_demo_VERSION_PATCH 1)

macro (use_c99)
        if (CMAKE_VERSION VERSION_LESS "3.1")
                if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
                        set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
                endif ()
        else ()
                set (CMAKE_C_STANDARD 99)
        endif ()
endmacro (use_c99)

use_c99 ()

set (
        CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules/"
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set (OperatingSystem "macos")
endif ()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set (OperatingSystem "linux")
endif ()

if (WIN32)
        set (OperatingSystem "windows")
endif ()

if (OperatingSystem STREQUAL "linux") # SET(OperatingSystem "linux")
        set (cpp_library "stdc++")

        # Store in CMAKE_DEB_HOST_ARCH var the current build architecture
        execute_process (
                COMMAND dpkg-architecture -qDEB_HOST_ARCH
                OUTPUT_VARIABLE CMAKE_DEB_HOST_ARCH
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        if (${CMAKE_DEB_HOST_ARCH} MATCHES "armhf")
                set (
                        link_directory /usr/lib/arm-linux-gnueabihf
                        ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/armhf
                ) # message("arm HARD FLOAT WOOO")
        elseif (${CMAKE_DEB_HOST_ARCH} MATCHES "i386")
                set (
                        link_directory /usr/lib/
                        ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86
                ) # message("eighty sixed
                message (
                        "FFFFFFFFFFFFFFFFFFFFFFf ${CMAKE_DEB_HOST_ARCH}"
                ) # message("SIXTY FOUR?!") WOOOOO")
        else ()
                message (
                        "ASDDDDDDDDDDDDDDDDDDDDDDDDDDD ${CMAKE_DEB_HOST_ARCH}"
                ) # message("SIXTY FOUR?!")
                set (
                        link_directory /usr/lib/x86_64-linux-gnu/
                        ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86_64
                )

        endif ()

        # link_directories(${link_directory} ${CMAKE_BINARY_DIR}
        # ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86_64)
        set (platform_libs X11 Xrandr Xi Xinerama z GLEW Xcursor)
endif (OperatingSystem STREQUAL "linux")

if (${OperatingSystem} MATCHES "macos")
        find_library (
                FREETYPE_LIB freetype $ENV{HOME}/art/r4/contrib/platform/darwin
        )
        find_library (
                PA_LIB portaudio $ENV{HOME}/art/r4/contrib/platform/darwin
        )
        find_library (COCOA_LIB Cocoa)
        find_library (IL_Library IL)
        find_library (PM_LIBRARY portaudio)
        find_library (AU_LIB AudioUnit)
        find_library (AT_LIB AudioToolbox)
        find_library (CA_LIB CoreAudio)
        find_library (CARBON_LIB Carbon)
        find_library (CM_LIB CoreMidi)
        find_library (CV_LIB CoreVideo)
        find_library (IO_LIB IOKit)
        find_library (GL_LIB OpenGL)
        link_directories (
                ${CMAKE_BINARY_DIR}
                # ${CMAKE_CURRENT_SOURCE_DIR}/contrib/wcm/build
                # ${CMAKE_CURRENT_SOURCE_DIR}/contrib/wcm
                # ${CMAKE_SOURCE_DIR}/demo/contrib/wcm/build
                /usr/local/lib
        )
        # message(                  "------"
        # ${CMAKE_CURRENT_SOURCE_DIR}/contrib/wcm/build )
endif ()

find_package (OpenGL)
if (OPENGL_FOUND)
        message ("OpenGL Correctly Found")
        include_directories (${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
        message ("OpenGL environment missing")
endif (OPENGL_FOUND)

file (
        GLOB
                sources
                src/*.c
                src/demos/*.c
                src/support/*.c
                src/input/*.c
                src/contrib/macos/*.m
                ${CMAKE_CURRENT_SOURCE_DIR}/../cjson/cJSON.c
)

# message(${sources})

add_executable (grdn_demo ${sources})

target_include_directories (
        grdn_demo
        PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs
                ${CMAKE_CURRENT_SOURCE_DIR}/contrib/wcm/src
                ${CMAKE_CURRENT_SOURCE_DIR}/contrib
                ${CMAKE_CURRENT_SOURCE_DIR}/../contrib
                ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/include
                ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib
                ${CMAKE_CURRENT_SOURCE_DIR}/contrib/ftgl/src
)

if (${OperatingSystem} MATCHES "macos")
        target_link_libraries (
                grdn_demo
                LINK_PUBLIC
                ${ADDITIONAL_LIBS}
                glfw
                ftgl
                ${GL_LIB}
                ${COCOA_LIB}
                ${CARBON_LIB}
                ${IO_LIB}
                ${CV_LIB}
        )

endif (${OperatingSystem} MATCHES "macos")

if (${OperatingSystem} MATCHES "linux")
        target_link_libraries (grdn_demo LINK_PUBLIC wsh glfw3 GL m X11 Xi)

endif ()
