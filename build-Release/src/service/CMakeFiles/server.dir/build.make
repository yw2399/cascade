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
CMAKE_SOURCE_DIR = /root/workspace/cascade

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/cascade/build-Release

# Include any dependencies generated for this target.
include src/service/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include src/service/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include src/service/CMakeFiles/server.dir/flags.make

src/service/CMakeFiles/server.dir/server.cpp.o: src/service/CMakeFiles/server.dir/flags.make
src/service/CMakeFiles/server.dir/server.cpp.o: ../src/service/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/cascade/build-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/service/CMakeFiles/server.dir/server.cpp.o"
	cd /root/workspace/cascade/build-Release/src/service && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server.cpp.o -c /root/workspace/cascade/src/service/server.cpp

src/service/CMakeFiles/server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server.cpp.i"
	cd /root/workspace/cascade/build-Release/src/service && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/cascade/src/service/server.cpp > CMakeFiles/server.dir/server.cpp.i

src/service/CMakeFiles/server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server.cpp.s"
	cd /root/workspace/cascade/build-Release/src/service && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/cascade/src/service/server.cpp -o CMakeFiles/server.dir/server.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

src/service/cascade_server: src/service/CMakeFiles/server.dir/server.cpp.o
src/service/cascade_server: src/service/CMakeFiles/server.dir/build.make
src/service/cascade_server: libcascade.so.1.0rc0
src/service/cascade_server: /root/opt-dev/lib/libderecho.so.2.2.2
src/service/cascade_server: /usr/local/lib/libfabric.so
src/service/cascade_server: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.5.0
src/service/cascade_server: /usr/lib/x86_64-linux-gnu/libcrypto.so
src/service/cascade_server: src/service/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/cascade/build-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cascade_server"
	cd /root/workspace/cascade/build-Release/src/service && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)
	cd /root/workspace/cascade/build-Release/src/service && /usr/bin/cmake -E copy_directory /root/workspace/cascade/src/service/cfg /root/workspace/cascade/build-Release/src/service/cfg

# Rule to build all files generated by this target.
src/service/CMakeFiles/server.dir/build: src/service/cascade_server

.PHONY : src/service/CMakeFiles/server.dir/build

src/service/CMakeFiles/server.dir/clean:
	cd /root/workspace/cascade/build-Release/src/service && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : src/service/CMakeFiles/server.dir/clean

src/service/CMakeFiles/server.dir/depend:
	cd /root/workspace/cascade/build-Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/cascade /root/workspace/cascade/src/service /root/workspace/cascade/build-Release /root/workspace/cascade/build-Release/src/service /root/workspace/cascade/build-Release/src/service/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/service/CMakeFiles/server.dir/depend

