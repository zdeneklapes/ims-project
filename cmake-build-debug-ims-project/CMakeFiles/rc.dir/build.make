# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.ZzpiupKbav

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.ZzpiupKbav/cmake-build-debug-ims-project

# Include any dependencies generated for this target.
include CMakeFiles/rc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rc.dir/flags.make

CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.o: CMakeFiles/rc.dir/flags.make
CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.o: ../third_party/simlib/examples/rc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.ZzpiupKbav/cmake-build-debug-ims-project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.o -c /tmp/tmp.ZzpiupKbav/third_party/simlib/examples/rc.cc

CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.ZzpiupKbav/third_party/simlib/examples/rc.cc > CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.i

CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.ZzpiupKbav/third_party/simlib/examples/rc.cc -o CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.s

# Object files for target rc
rc_OBJECTS = \
"CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.o"

# External object files for target rc
rc_EXTERNAL_OBJECTS =

rc: CMakeFiles/rc.dir/third_party/simlib/examples/rc.cc.o
rc: CMakeFiles/rc.dir/build.make
rc: /usr/local/lib/libsimlib.so
rc: CMakeFiles/rc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.ZzpiupKbav/cmake-build-debug-ims-project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rc.dir/build: rc

.PHONY : CMakeFiles/rc.dir/build

CMakeFiles/rc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rc.dir/clean

CMakeFiles/rc.dir/depend:
	cd /tmp/tmp.ZzpiupKbav/cmake-build-debug-ims-project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.ZzpiupKbav /tmp/tmp.ZzpiupKbav /tmp/tmp.ZzpiupKbav/cmake-build-debug-ims-project /tmp/tmp.ZzpiupKbav/cmake-build-debug-ims-project /tmp/tmp.ZzpiupKbav/cmake-build-debug-ims-project/CMakeFiles/rc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rc.dir/depend
