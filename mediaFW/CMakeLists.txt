cmake_minimum_required(VERSION 3.12)
project(mediaFW)

set(CMAKE_CXX_STANDARD 17)

find_package(Libssh2 REQUIRED CONFIG)

add_executable(mediaFW main.cpp Cli.cpp Cli.h Connection.cpp Connection.h)

target_link_libraries(mediaFW Libssh2::libssh2)