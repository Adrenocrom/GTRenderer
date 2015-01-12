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
include CMakeFiles/RayTracer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RayTracer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RayTracer.dir/flags.make

CMakeFiles/RayTracer.dir/Vector3.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/Vector3.cpp.o: Vector3.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RayTracer.dir/Vector3.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/Vector3.cpp.o -c /home/josef/Dokumente/Studium/GTRenderer/raytracer/Vector3.cpp

CMakeFiles/RayTracer.dir/Vector3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/Vector3.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/josef/Dokumente/Studium/GTRenderer/raytracer/Vector3.cpp > CMakeFiles/RayTracer.dir/Vector3.cpp.i

CMakeFiles/RayTracer.dir/Vector3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/Vector3.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/josef/Dokumente/Studium/GTRenderer/raytracer/Vector3.cpp -o CMakeFiles/RayTracer.dir/Vector3.cpp.s

CMakeFiles/RayTracer.dir/Vector3.cpp.o.requires:
.PHONY : CMakeFiles/RayTracer.dir/Vector3.cpp.o.requires

CMakeFiles/RayTracer.dir/Vector3.cpp.o.provides: CMakeFiles/RayTracer.dir/Vector3.cpp.o.requires
	$(MAKE) -f CMakeFiles/RayTracer.dir/build.make CMakeFiles/RayTracer.dir/Vector3.cpp.o.provides.build
.PHONY : CMakeFiles/RayTracer.dir/Vector3.cpp.o.provides

CMakeFiles/RayTracer.dir/Vector3.cpp.o.provides.build: CMakeFiles/RayTracer.dir/Vector3.cpp.o

CMakeFiles/RayTracer.dir/Sphere.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/Sphere.cpp.o: Sphere.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RayTracer.dir/Sphere.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/Sphere.cpp.o -c /home/josef/Dokumente/Studium/GTRenderer/raytracer/Sphere.cpp

CMakeFiles/RayTracer.dir/Sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/Sphere.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/josef/Dokumente/Studium/GTRenderer/raytracer/Sphere.cpp > CMakeFiles/RayTracer.dir/Sphere.cpp.i

CMakeFiles/RayTracer.dir/Sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/Sphere.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/josef/Dokumente/Studium/GTRenderer/raytracer/Sphere.cpp -o CMakeFiles/RayTracer.dir/Sphere.cpp.s

CMakeFiles/RayTracer.dir/Sphere.cpp.o.requires:
.PHONY : CMakeFiles/RayTracer.dir/Sphere.cpp.o.requires

CMakeFiles/RayTracer.dir/Sphere.cpp.o.provides: CMakeFiles/RayTracer.dir/Sphere.cpp.o.requires
	$(MAKE) -f CMakeFiles/RayTracer.dir/build.make CMakeFiles/RayTracer.dir/Sphere.cpp.o.provides.build
.PHONY : CMakeFiles/RayTracer.dir/Sphere.cpp.o.provides

CMakeFiles/RayTracer.dir/Sphere.cpp.o.provides.build: CMakeFiles/RayTracer.dir/Sphere.cpp.o

CMakeFiles/RayTracer.dir/Ray.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/Ray.cpp.o: Ray.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RayTracer.dir/Ray.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/Ray.cpp.o -c /home/josef/Dokumente/Studium/GTRenderer/raytracer/Ray.cpp

CMakeFiles/RayTracer.dir/Ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/Ray.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/josef/Dokumente/Studium/GTRenderer/raytracer/Ray.cpp > CMakeFiles/RayTracer.dir/Ray.cpp.i

CMakeFiles/RayTracer.dir/Ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/Ray.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/josef/Dokumente/Studium/GTRenderer/raytracer/Ray.cpp -o CMakeFiles/RayTracer.dir/Ray.cpp.s

CMakeFiles/RayTracer.dir/Ray.cpp.o.requires:
.PHONY : CMakeFiles/RayTracer.dir/Ray.cpp.o.requires

CMakeFiles/RayTracer.dir/Ray.cpp.o.provides: CMakeFiles/RayTracer.dir/Ray.cpp.o.requires
	$(MAKE) -f CMakeFiles/RayTracer.dir/build.make CMakeFiles/RayTracer.dir/Ray.cpp.o.provides.build
.PHONY : CMakeFiles/RayTracer.dir/Ray.cpp.o.provides

CMakeFiles/RayTracer.dir/Ray.cpp.o.provides.build: CMakeFiles/RayTracer.dir/Ray.cpp.o

CMakeFiles/RayTracer.dir/LightSource.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/LightSource.cpp.o: LightSource.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RayTracer.dir/LightSource.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/LightSource.cpp.o -c /home/josef/Dokumente/Studium/GTRenderer/raytracer/LightSource.cpp

CMakeFiles/RayTracer.dir/LightSource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/LightSource.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/josef/Dokumente/Studium/GTRenderer/raytracer/LightSource.cpp > CMakeFiles/RayTracer.dir/LightSource.cpp.i

CMakeFiles/RayTracer.dir/LightSource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/LightSource.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/josef/Dokumente/Studium/GTRenderer/raytracer/LightSource.cpp -o CMakeFiles/RayTracer.dir/LightSource.cpp.s

CMakeFiles/RayTracer.dir/LightSource.cpp.o.requires:
.PHONY : CMakeFiles/RayTracer.dir/LightSource.cpp.o.requires

CMakeFiles/RayTracer.dir/LightSource.cpp.o.provides: CMakeFiles/RayTracer.dir/LightSource.cpp.o.requires
	$(MAKE) -f CMakeFiles/RayTracer.dir/build.make CMakeFiles/RayTracer.dir/LightSource.cpp.o.provides.build
.PHONY : CMakeFiles/RayTracer.dir/LightSource.cpp.o.provides

CMakeFiles/RayTracer.dir/LightSource.cpp.o.provides.build: CMakeFiles/RayTracer.dir/LightSource.cpp.o

CMakeFiles/RayTracer.dir/main.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RayTracer.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/main.cpp.o -c /home/josef/Dokumente/Studium/GTRenderer/raytracer/main.cpp

CMakeFiles/RayTracer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/josef/Dokumente/Studium/GTRenderer/raytracer/main.cpp > CMakeFiles/RayTracer.dir/main.cpp.i

CMakeFiles/RayTracer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/josef/Dokumente/Studium/GTRenderer/raytracer/main.cpp -o CMakeFiles/RayTracer.dir/main.cpp.s

CMakeFiles/RayTracer.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/RayTracer.dir/main.cpp.o.requires

CMakeFiles/RayTracer.dir/main.cpp.o.provides: CMakeFiles/RayTracer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/RayTracer.dir/build.make CMakeFiles/RayTracer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/RayTracer.dir/main.cpp.o.provides

CMakeFiles/RayTracer.dir/main.cpp.o.provides.build: CMakeFiles/RayTracer.dir/main.cpp.o

CMakeFiles/RayTracer.dir/GTRenderer.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/GTRenderer.cpp.o: GTRenderer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RayTracer.dir/GTRenderer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RayTracer.dir/GTRenderer.cpp.o -c /home/josef/Dokumente/Studium/GTRenderer/raytracer/GTRenderer.cpp

CMakeFiles/RayTracer.dir/GTRenderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/GTRenderer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/josef/Dokumente/Studium/GTRenderer/raytracer/GTRenderer.cpp > CMakeFiles/RayTracer.dir/GTRenderer.cpp.i

CMakeFiles/RayTracer.dir/GTRenderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/GTRenderer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/josef/Dokumente/Studium/GTRenderer/raytracer/GTRenderer.cpp -o CMakeFiles/RayTracer.dir/GTRenderer.cpp.s

CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.requires:
.PHONY : CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.requires

CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.provides: CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.requires
	$(MAKE) -f CMakeFiles/RayTracer.dir/build.make CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.provides.build
.PHONY : CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.provides

CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.provides.build: CMakeFiles/RayTracer.dir/GTRenderer.cpp.o

# Object files for target RayTracer
RayTracer_OBJECTS = \
"CMakeFiles/RayTracer.dir/Vector3.cpp.o" \
"CMakeFiles/RayTracer.dir/Sphere.cpp.o" \
"CMakeFiles/RayTracer.dir/Ray.cpp.o" \
"CMakeFiles/RayTracer.dir/LightSource.cpp.o" \
"CMakeFiles/RayTracer.dir/main.cpp.o" \
"CMakeFiles/RayTracer.dir/GTRenderer.cpp.o"

# External object files for target RayTracer
RayTracer_EXTERNAL_OBJECTS =

libRayTracer.a: CMakeFiles/RayTracer.dir/Vector3.cpp.o
libRayTracer.a: CMakeFiles/RayTracer.dir/Sphere.cpp.o
libRayTracer.a: CMakeFiles/RayTracer.dir/Ray.cpp.o
libRayTracer.a: CMakeFiles/RayTracer.dir/LightSource.cpp.o
libRayTracer.a: CMakeFiles/RayTracer.dir/main.cpp.o
libRayTracer.a: CMakeFiles/RayTracer.dir/GTRenderer.cpp.o
libRayTracer.a: CMakeFiles/RayTracer.dir/build.make
libRayTracer.a: CMakeFiles/RayTracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libRayTracer.a"
	$(CMAKE_COMMAND) -P CMakeFiles/RayTracer.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RayTracer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RayTracer.dir/build: libRayTracer.a
.PHONY : CMakeFiles/RayTracer.dir/build

CMakeFiles/RayTracer.dir/requires: CMakeFiles/RayTracer.dir/Vector3.cpp.o.requires
CMakeFiles/RayTracer.dir/requires: CMakeFiles/RayTracer.dir/Sphere.cpp.o.requires
CMakeFiles/RayTracer.dir/requires: CMakeFiles/RayTracer.dir/Ray.cpp.o.requires
CMakeFiles/RayTracer.dir/requires: CMakeFiles/RayTracer.dir/LightSource.cpp.o.requires
CMakeFiles/RayTracer.dir/requires: CMakeFiles/RayTracer.dir/main.cpp.o.requires
CMakeFiles/RayTracer.dir/requires: CMakeFiles/RayTracer.dir/GTRenderer.cpp.o.requires
.PHONY : CMakeFiles/RayTracer.dir/requires

CMakeFiles/RayTracer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RayTracer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RayTracer.dir/clean

CMakeFiles/RayTracer.dir/depend:
	cd /home/josef/Dokumente/Studium/GTRenderer/raytracer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer /home/josef/Dokumente/Studium/GTRenderer/raytracer/CMakeFiles/RayTracer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RayTracer.dir/depend
