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
CMAKE_COMMAND = /opt/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mjonsson/repo/mediaFW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mjonsson/repo/mediaFW/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mediaFW.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mediaFW.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mediaFW.dir/flags.make

CMakeFiles/mediaFW.dir/main.cpp.o: CMakeFiles/mediaFW.dir/flags.make
CMakeFiles/mediaFW.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mjonsson/repo/mediaFW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mediaFW.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mediaFW.dir/main.cpp.o -c /home/mjonsson/repo/mediaFW/main.cpp

CMakeFiles/mediaFW.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mediaFW.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mjonsson/repo/mediaFW/main.cpp > CMakeFiles/mediaFW.dir/main.cpp.i

CMakeFiles/mediaFW.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mediaFW.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mjonsson/repo/mediaFW/main.cpp -o CMakeFiles/mediaFW.dir/main.cpp.s

CMakeFiles/mediaFW.dir/Cli.cpp.o: CMakeFiles/mediaFW.dir/flags.make
CMakeFiles/mediaFW.dir/Cli.cpp.o: ../Cli.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mjonsson/repo/mediaFW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mediaFW.dir/Cli.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mediaFW.dir/Cli.cpp.o -c /home/mjonsson/repo/mediaFW/Cli.cpp

CMakeFiles/mediaFW.dir/Cli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mediaFW.dir/Cli.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mjonsson/repo/mediaFW/Cli.cpp > CMakeFiles/mediaFW.dir/Cli.cpp.i

CMakeFiles/mediaFW.dir/Cli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mediaFW.dir/Cli.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mjonsson/repo/mediaFW/Cli.cpp -o CMakeFiles/mediaFW.dir/Cli.cpp.s

CMakeFiles/mediaFW.dir/Connection.cpp.o: CMakeFiles/mediaFW.dir/flags.make
CMakeFiles/mediaFW.dir/Connection.cpp.o: ../Connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mjonsson/repo/mediaFW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mediaFW.dir/Connection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mediaFW.dir/Connection.cpp.o -c /home/mjonsson/repo/mediaFW/Connection.cpp

CMakeFiles/mediaFW.dir/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mediaFW.dir/Connection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mjonsson/repo/mediaFW/Connection.cpp > CMakeFiles/mediaFW.dir/Connection.cpp.i

CMakeFiles/mediaFW.dir/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mediaFW.dir/Connection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mjonsson/repo/mediaFW/Connection.cpp -o CMakeFiles/mediaFW.dir/Connection.cpp.s

# Object files for target mediaFW
mediaFW_OBJECTS = \
"CMakeFiles/mediaFW.dir/main.cpp.o" \
"CMakeFiles/mediaFW.dir/Cli.cpp.o" \
"CMakeFiles/mediaFW.dir/Connection.cpp.o"

# External object files for target mediaFW
mediaFW_EXTERNAL_OBJECTS =

mediaFW: CMakeFiles/mediaFW.dir/main.cpp.o
mediaFW: CMakeFiles/mediaFW.dir/Cli.cpp.o
mediaFW: CMakeFiles/mediaFW.dir/Connection.cpp.o
mediaFW: CMakeFiles/mediaFW.dir/build.make
mediaFW: CMakeFiles/mediaFW.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mjonsson/repo/mediaFW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mediaFW"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mediaFW.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mediaFW.dir/build: mediaFW

.PHONY : CMakeFiles/mediaFW.dir/build

CMakeFiles/mediaFW.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mediaFW.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mediaFW.dir/clean

CMakeFiles/mediaFW.dir/depend:
	cd /home/mjonsson/repo/mediaFW/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mjonsson/repo/mediaFW /home/mjonsson/repo/mediaFW /home/mjonsson/repo/mediaFW/cmake-build-debug /home/mjonsson/repo/mediaFW/cmake-build-debug /home/mjonsson/repo/mediaFW/cmake-build-debug/CMakeFiles/mediaFW.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mediaFW.dir/depend

