cmake_minimum_required(VERSION 3.12)
project(mediaFW)

set(CMAKE_CXX_STANDARD 17)

# LIBSSH
find_path(LIBSSH_INCLUDE_DIR libssh.h)
find_package(LIBSSH REQUIRED CONFIG)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# INCLUDE TEST
include_directories(test)
# INCLUDE HEADERS
include_directories(inc)
# INCLUDE DATABASE HEADERS
include_directories(inc/Database)
# JSON
include_directories(inc/json)
# GOOGLE TEST
include_directories(contrib/googletest)

# DOXYGEN
find_package(Doxygen)
if(DOXYGEN_FOUND)

    set(DOXYGEN_INPUT ${SOURCE_FILES})
    set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    add_custom_command(
            OUTPUT ${DOXYGEN_OUTPUT}
            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${DOXYGEN_INPUT}
    )

    add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

    add_custom_target(apidoc_forced
            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )

endif(DOXYGEN_FOUND)


set(SrcFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/src/Cli.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Connection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Client.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/JsonParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/json/jsoncpp.cpp
        )

set(IncFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/inc/Cli.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Connection.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Client.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Database/MovieDatabase.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Database/Database.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Database/DatabaseItem.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/JsonParser.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/json/json.h)

set(TestFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/test/Fixtures.h
        ${CMAKE_CURRENT_LIST_DIR}/test/Mocks.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Database/Test_Database.h)

# GOOGLE TEST
enable_testing()
add_custom_target(check COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --verbose)
add_subdirectory("contrib/googletest")


add_executable(mediaFW ${IncFilesToInclude} ${SrcFilesToInclude} ${TestFilesToInclude})
target_link_libraries(mediaFW googletest)
target_link_libraries(mediaFW ssh)
target_link_libraries(mediaFW jsoncpp)
## add the binary tree to the search path for include files
## so that we will find TutorialConfig.h
#include_directories("${PROJECT_BINARY_DIR}")