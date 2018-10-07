cmake_minimum_required(VERSION 3.12)
project(mediaFW)

find_path(LIBSSH_INCLUDE_DIR libssh.h)

set(CMAKE_CXX_STANDARD 17)
find_package(LIBSSH REQUIRED CONFIG)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SrcFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/src/Cli.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Connection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Client.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        )

set(IncFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/inc/Cli.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Connection.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Client.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/MovieDatabase.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Database.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/DatabaseItem.h
        )


enable_testing()

add_custom_target(check COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --verbose)
add_subdirectory("contrib/googletest")

include_directories(inc)
include_directories(contrib/googletest)

add_executable(mediaFW ${IncFilesToInclude} ${SrcFilesToInclude})
target_link_libraries(mediaFW googletest)
target_link_libraries(mediaFW ssh)
## add the binary tree to the search path for include files
## so that we will find TutorialConfig.h
#include_directories("${PROJECT_BINARY_DIR}")