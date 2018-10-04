cmake_minimum_required(VERSION 3.12)
project(mediaFW)

set(CMAKE_CXX_STANDARD 17)
find_package(Libssh2 REQUIRED CONFIG)

set(SrcFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/src/Cli.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Connection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Client.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/MovieDatabase.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        )

set(IncFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/inc/Cli.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Connection.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Client.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/MovieDatabase.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Database.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/DatabaseItem.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/libssh2_config.h
        )


add_executable(mediaFW ${IncFilesToInclude} ${SrcFilesToInclude})

target_link_libraries(mediaFW Libssh2::libssh2)

## add the binary tree to the search path for include files
## so that we will find TutorialConfig.h
#include_directories("${PROJECT_BINARY_DIR}")