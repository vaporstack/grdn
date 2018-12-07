cmake_minimum_required(VERSION 3.0)
project(test_grdn)
set(test_grdn_VERSION_MAJOR 0)
set(test_grdn_VERSION_MINOR 0)
set(test_grdn_VERSION_PATCH 1)

file(GLOB sources *.c)
message(${sources})

find_package(OpenGL)
if(OPENGL_FOUND)
  message("OpenGL Correctly Found")
  include_directories(${OPENGL_INCLUDE_DIR})
else(OPENGL_FOUND)
  message("OpenGL environment missing")
endif(OPENGL_FOUND)

link_directories(test_grdn PUBLIC ${contrib_lib_dir})

add_executable(test_grdn ${sources})

target_include_directories(test_grdn PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)
target_include_directories(test_grdn PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/include)
target_include_directories(test_grdn PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib)
if(${OperatingSystem} MATCHES "macos")
  find_library(GLUT_LIB GLUT)

  target_link_libraries(
    test_grdn LINK_PUBLIC  ${GLUT_LIB} grdn drw ftgl r4 GLUT z c )
endif()

if(${OperatingSystem} MATCHES "linux")
  target_link_libraries(test_grdn LINK_PUBLIC grdn drw GLEW ftgl r4 glut c stdc++ z)

endif()

