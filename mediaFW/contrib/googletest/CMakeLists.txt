add_library(googletest src/gtest-all.cc)
target_include_directories(googletest PUBLIC .)
target_link_libraries(googletest Threads::Threads)