#Tiny Object Loader Cmake configuration file.
#This configures the Cmake system with multiple properties, depending
#on the platform and configuration it is set to build in.
project(tinyobjloader)
cmake_minimum_required(VERSION 2.8.6)

#Folder Shortcuts
set(TINYOBJLOADEREXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

set(tinyobjloader-Source
	${CMAKE_CURRENT_SOURCE_DIR}/tiny_obj_loader.h
	${CMAKE_CURRENT_SOURCE_DIR}/tiny_obj_loader.cc
	)

set(tinyobjloader-Test-Source
	${CMAKE_CURRENT_SOURCE_DIR}/test.cc
	)

set(tinyobjloader-examples-objsticher
	${TINYOBJLOADEREXAMPLES_DIR}/obj_sticher/obj_writer.h
	${TINYOBJLOADEREXAMPLES_DIR}/obj_sticher/obj_writer.cc
	${TINYOBJLOADEREXAMPLES_DIR}/obj_sticher/obj_sticher.cc
	)

set(LIBRARY_NAME tinyobjloader)
if(DEFINED USE_DOUBLE)
	# this message is mainly there to prevent an unused variable warning
	message("NOTE: Building with double instead of float due to USE_DOUBLE=" ${USE_DOUBLE})
	add_definitions(-DTINY_OBJ_USE_DOUBLE)
	set(LIBRARY_NAME tinyobjloader_double)
else()
set(LIBRARY_NAME tinyobjloader)
endif()

add_library(${LIBRARY_NAME}
			${tinyobjloader-Source}
	)

option(TINYOBJLOADER_BUILD_TEST_LOADER "Build Test Loader Application" OFF)

if(TINYOBJLOADER_BUILD_TEST_LOADER)
  add_executable(test_loader ${tinyobjloader-Test-Source})
  target_link_libraries(test_loader ${LIBRARY_NAME})
endif()

option(TINYOBJLOADER_BUILD_OBJ_STICHER "Build OBJ Sticher Application" OFF)
if (TINYOBJLOADER_BUILD_OBJ_STICHER)
  add_executable(obj_sticher ${tinyobjloader-examples-objsticher})
  target_link_libraries(obj_sticher ${LIBRARY_NAME})

  install ( TARGETS
    obj_sticher
    DESTINATION
    bin
    )
endif()

#Installation
install ( TARGETS
  ${LIBRARY_NAME}
  DESTINATION
  lib
  )
install ( FILES
  tiny_obj_loader.h
  DESTINATION
  include
  )
