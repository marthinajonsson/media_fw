add_library(googletest src/gtest-all.cc)
add_library(googlemock src/gmock-all.cc)
target_include_directories(googlemock PUBLIC .)
target_link_libraries(googlemock Threads::Threads)