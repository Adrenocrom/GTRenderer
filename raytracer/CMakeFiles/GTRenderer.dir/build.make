# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/josef/Dokumente/Studium/GTRenderer/raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/josef/Dokumente/Studium/GTRenderer/raytracer

# Include any dependencies generated for this target.
include CMakeFiles/GTRenderer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GTRenderer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GTRenderer.dir/flags.make

CMakeFiles/GTRenderer.dir/main.cpp.o: CMakeFiles/GTRenderer.dir/flags.make
CMakeFiles/GTRenderer.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/GTRenderer.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/GTRenderer.dir/main.cpp.o -c /home/josef/Dokumente/Studium/GTRenderer/raytracer/main.cpp

CMakeFiles/GTRenderer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GTRenderer.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/josef/Dokumente/Studium/GTRenderer/raytracer/main.cpp > CMakeFiles/GTRenderer.dir/main.cpp.i

CMakeFiles/GTRenderer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GTRenderer.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/josef/Dokumente/Studium/GTRenderer/raytracer/main.cpp -o CMakeFiles/GTRenderer.dir/main.cpp.s

CMakeFiles/GTRenderer.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/GTRenderer.dir/main.cpp.o.requires

CMakeFiles/GTRenderer.dir/main.cpp.o.provides: CMakeFiles/GTRenderer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/GTRenderer.dir/build.make CMakeFiles/GTRenderer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/GTRenderer.dir/main.cpp.o.provides

CMakeFiles/GTRenderer.dir/main.cpp.o.provides.build: CMakeFiles/GTRenderer.dir/main.cpp.o

# Object files for target GTRenderer
GTRenderer_OBJECTS = \
"CMakeFiles/GTRenderer.dir/main.cpp.o"

# External object files for target GTRenderer
GTRenderer_EXTERNAL_OBJECTS =

GTRenderer: CMakeFiles/GTRenderer.dir/main.cpp.o
GTRenderer: CMakeFiles/GTRenderer.dir/build.make
GTRenderer: libRayTracer.a
GTRenderer: CMakeFiles/GTRenderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable GTRenderer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GTRenderer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GTRenderer.dir/build: GTRenderer
.PHONY : CMakeFiles/GTRenderer.dir/build

CMakeFiles/GTRenderer.dir/requires: CMakeFiles/GTRenderer.dir/main.cpp.o.requires
.PHONY : CMakeFiles/GTRenderer.dir/requires

CMakeFiles/GTRenderer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GTRenderer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GTRenderer.dir/clean

CMakeFiles/GTRenderer.dir/depend:
	cd /home/josef/Dokumente/Studium/GTRenderer/raytracer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles/GTRenderer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GTRenderer.dir/depend

