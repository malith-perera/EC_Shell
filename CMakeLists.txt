cmake_minimum_required(VERSION 3.10.2)
project (ec)

set (CMAKE_BUILD_TYPE DEBUG)  #Release type

# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  `--libs --cflags` -ggdb3 -O0 --std=c11 -Wall image -lm")
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else ()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif ()
endif ()

get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

# Set bin directory
set (BIN_DIR ${PROJECT_SOURCE_DIR})

# If shared lib is not build in the same CMake project of executable
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# If shared library is built in the same CMake project
#set(CMAKE_INSTALL_RPATH "${PARENT_DIR}/eclib")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set (PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src)

set (PROJECT_LINK_LIBS libEC.so)
set (PROJECT_LINK_DIRS ${PARENT_DIR}/EC/lib /usr/lib/ec)
link_directories (${PROJECT_LINK_DIRS})

include_directories (${PROJECT_INCLUDE_DIRS} ${PARENT_DIR}/EC/include)

#file(GLOB...) allows wildcard additions
file (GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

#Generate executable from the sources
add_executable (${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC ${PROJECT_LINK_LIBS} m)

# Use "sudo make install" to set the location /usr/lib
#install (TARGETS ${PROJECT_NAME} DESTINATION ${BIN_DIR})

#message ("${PARENT_DIR}")
