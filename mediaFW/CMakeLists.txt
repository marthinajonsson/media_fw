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
include_directories(inc/database)
# JSON
include_directories(inc/json)
# GOOGLE TEST
include_directories(contrib/googletest)
include_directories(src/unittests)
include_directories(inc/unittests)


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
        ${CMAKE_CURRENT_LIST_DIR}/src/Client.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/JsonParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/json/jsoncpp.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/MediaHandler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SshConnector.cpp)

set(IncFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/inc/Cli.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Connection.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Client.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/database/MovieDatabase.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/database/Database.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/database/DatabaseItem.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/JsonParser.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/json/json.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/MediaHandler.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Util.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/ifc/Logger.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/StatusLogger.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/ifc/Observer.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/ifc/Subject.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/ifc/Connector.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/ConnectionStream.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/SshConnector.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/Request.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/ifc/Parser.h inc/database/SeriesDatabase.h)

set(TestFilesToInclude
        ${CMAKE_CURRENT_LIST_DIR}/inc/unittests/Test_Database.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/unittests/Test_Json.h
        ${CMAKE_CURRENT_LIST_DIR}/inc/unittests/Test_Logger.h
        ${CMAKE_CURRENT_LIST_DIR}/src/unittests/Test_Cli.h
        ${CMAKE_CURRENT_LIST_DIR}/test/Fixtures.h
        ${CMAKE_CURRENT_LIST_DIR}/test/Mocks.h
        ${CMAKE_CURRENT_LIST_DIR}/test/test_main.cpp test/Test_Startup.h)


# GOOGLE TEST
enable_testing()
add_custom_target(check COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --verbose)
add_subdirectory("contrib/googletest")

add_executable(mediaFW ${IncFilesToInclude} ${SrcFilesToInclude} ${TestFilesToInclude})
target_link_libraries(mediaFW googlemock)
target_link_libraries(mediaFW googletest)
target_link_libraries(mediaFW ssh)
target_link_libraries(mediaFW jsoncpp)
## add the binary tree to the search path for include files
## so that we will find TutorialConfig.h
#include_directories("${PROJECT_BINARY_DIR}")