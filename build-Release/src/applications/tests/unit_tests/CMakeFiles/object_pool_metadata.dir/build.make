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
include src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/depend.make

# Include the progress variables for this target.
include src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/progress.make

# Include the compile flags for this target's objects.
include src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/flags.make

src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.o: src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/flags.make
src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.o: ../src/applications/tests/unit_tests/object_pool_metadata.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/cascade/build-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.o"
	cd /root/workspace/cascade/build-Release/src/applications/tests/unit_tests && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.o -c /root/workspace/cascade/src/applications/tests/unit_tests/object_pool_metadata.cpp

src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.i"
	cd /root/workspace/cascade/build-Release/src/applications/tests/unit_tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/cascade/src/applications/tests/unit_tests/object_pool_metadata.cpp > CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.i

src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.s"
	cd /root/workspace/cascade/build-Release/src/applications/tests/unit_tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/cascade/src/applications/tests/unit_tests/object_pool_metadata.cpp -o CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.s

# Object files for target object_pool_metadata
object_pool_metadata_OBJECTS = \
"CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.o"

# External object files for target object_pool_metadata
object_pool_metadata_EXTERNAL_OBJECTS =

src/applications/tests/unit_tests/object_pool_metadata: src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/object_pool_metadata.cpp.o
src/applications/tests/unit_tests/object_pool_metadata: src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/build.make
src/applications/tests/unit_tests/object_pool_metadata: libcascade.so.1.0rc0
src/applications/tests/unit_tests/object_pool_metadata: /root/opt-dev/lib/libderecho.so.2.2.2
src/applications/tests/unit_tests/object_pool_metadata: /usr/local/lib/libfabric.so
src/applications/tests/unit_tests/object_pool_metadata: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.5.0
src/applications/tests/unit_tests/object_pool_metadata: /usr/lib/x86_64-linux-gnu/libcrypto.so
src/applications/tests/unit_tests/object_pool_metadata: src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/cascade/build-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable object_pool_metadata"
	cd /root/workspace/cascade/build-Release/src/applications/tests/unit_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/object_pool_metadata.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/build: src/applications/tests/unit_tests/object_pool_metadata

.PHONY : src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/build

src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/clean:
	cd /root/workspace/cascade/build-Release/src/applications/tests/unit_tests && $(CMAKE_COMMAND) -P CMakeFiles/object_pool_metadata.dir/cmake_clean.cmake
.PHONY : src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/clean

src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/depend:
	cd /root/workspace/cascade/build-Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/cascade /root/workspace/cascade/src/applications/tests/unit_tests /root/workspace/cascade/build-Release /root/workspace/cascade/build-Release/src/applications/tests/unit_tests /root/workspace/cascade/build-Release/src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/applications/tests/unit_tests/CMakeFiles/object_pool_metadata.dir/depend

