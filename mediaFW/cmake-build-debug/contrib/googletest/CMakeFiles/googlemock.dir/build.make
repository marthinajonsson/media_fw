# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mjonsson/clion_src/clion-2018.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mjonsson/clion_src/clion-2018.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mjonsson/repo/media_fw/mediaFW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug

# Include any dependencies generated for this target.
include contrib/googletest/CMakeFiles/googlemock.dir/depend.make

# Include the progress variables for this target.
include contrib/googletest/CMakeFiles/googlemock.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/googletest/CMakeFiles/googlemock.dir/flags.make

contrib/googletest/CMakeFiles/googlemock.dir/src/gmock-all.cc.o: contrib/googletest/CMakeFiles/googlemock.dir/flags.make
contrib/googletest/CMakeFiles/googlemock.dir/src/gmock-all.cc.o: ../contrib/googletest/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/googletest/CMakeFiles/googlemock.dir/src/gmock-all.cc.o"
	cd /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/googlemock.dir/src/gmock-all.cc.o -c /home/mjonsson/repo/media_fw/mediaFW/contrib/googletest/src/gmock-all.cc

contrib/googletest/CMakeFiles/googlemock.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/googlemock.dir/src/gmock-all.cc.i"
	cd /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mjonsson/repo/media_fw/mediaFW/contrib/googletest/src/gmock-all.cc > CMakeFiles/googlemock.dir/src/gmock-all.cc.i

contrib/googletest/CMakeFiles/googlemock.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/googlemock.dir/src/gmock-all.cc.s"
	cd /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mjonsson/repo/media_fw/mediaFW/contrib/googletest/src/gmock-all.cc -o CMakeFiles/googlemock.dir/src/gmock-all.cc.s

# Object files for target googlemock
googlemock_OBJECTS = \
"CMakeFiles/googlemock.dir/src/gmock-all.cc.o"

# External object files for target googlemock
googlemock_EXTERNAL_OBJECTS =

contrib/googletest/libgooglemock.a: contrib/googletest/CMakeFiles/googlemock.dir/src/gmock-all.cc.o
contrib/googletest/libgooglemock.a: contrib/googletest/CMakeFiles/googlemock.dir/build.make
contrib/googletest/libgooglemock.a: contrib/googletest/CMakeFiles/googlemock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgooglemock.a"
	cd /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest && $(CMAKE_COMMAND) -P CMakeFiles/googlemock.dir/cmake_clean_target.cmake
	cd /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/googlemock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/googletest/CMakeFiles/googlemock.dir/build: contrib/googletest/libgooglemock.a

.PHONY : contrib/googletest/CMakeFiles/googlemock.dir/build

contrib/googletest/CMakeFiles/googlemock.dir/clean:
	cd /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest && $(CMAKE_COMMAND) -P CMakeFiles/googlemock.dir/cmake_clean.cmake
.PHONY : contrib/googletest/CMakeFiles/googlemock.dir/clean

contrib/googletest/CMakeFiles/googlemock.dir/depend:
	cd /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mjonsson/repo/media_fw/mediaFW /home/mjonsson/repo/media_fw/mediaFW/contrib/googletest /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest /home/mjonsson/repo/media_fw/mediaFW/cmake-build-debug/contrib/googletest/CMakeFiles/googlemock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/googletest/CMakeFiles/googlemock.dir/depend

