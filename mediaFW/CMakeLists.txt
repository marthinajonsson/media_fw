cmake_minimum_required(VERSION 3.12)
project(mediaFW)

set(CMAKE_CXX_STANDARD 17)
find_package(Libssh2 REQUIRED CONFIG)

subdirs(src)
include_directories(${MyProject_SOURCE_DIR}/inc)

add_executable(mediaFW main.cpp Cli.cpp Cli.h Connection.cpp Connection.h Database.h DatabaseItem.h Client.cpp Client.h MovieDatabase.cpp MovieDatabase.h)

target_link_libraries(mediaFW Libssh2::libssh2)

## add the binary tree to the search path for include files
## so that we will find TutorialConfig.h
#include_directories("${PROJECT_BINARY_DIR}")