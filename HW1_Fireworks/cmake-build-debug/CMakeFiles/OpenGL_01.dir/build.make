# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/vladpc/Downloads/CLion-2018.3.4/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/vladpc/Downloads/CLion-2018.3.4/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vladpc/GraphicsHW/HW1_Fireworks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OpenGL_01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGL_01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGL_01.dir/flags.make

CMakeFiles/OpenGL_01.dir/Homework1.cpp.o: CMakeFiles/OpenGL_01.dir/flags.make
CMakeFiles/OpenGL_01.dir/Homework1.cpp.o: ../Homework1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGL_01.dir/Homework1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OpenGL_01.dir/Homework1.cpp.o -c /home/vladpc/GraphicsHW/HW1_Fireworks/Homework1.cpp

CMakeFiles/OpenGL_01.dir/Homework1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGL_01.dir/Homework1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladpc/GraphicsHW/HW1_Fireworks/Homework1.cpp > CMakeFiles/OpenGL_01.dir/Homework1.cpp.i

CMakeFiles/OpenGL_01.dir/Homework1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGL_01.dir/Homework1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladpc/GraphicsHW/HW1_Fireworks/Homework1.cpp -o CMakeFiles/OpenGL_01.dir/Homework1.cpp.s

# Object files for target OpenGL_01
OpenGL_01_OBJECTS = \
"CMakeFiles/OpenGL_01.dir/Homework1.cpp.o"

# External object files for target OpenGL_01
OpenGL_01_EXTERNAL_OBJECTS =

OpenGL_01: CMakeFiles/OpenGL_01.dir/Homework1.cpp.o
OpenGL_01: CMakeFiles/OpenGL_01.dir/build.make
OpenGL_01: /usr/lib/x86_64-linux-gnu/libOpenGL.so
OpenGL_01: /usr/lib/x86_64-linux-gnu/libGLX.so
OpenGL_01: /usr/lib/x86_64-linux-gnu/libGLU.so
OpenGL_01: /usr/lib/x86_64-linux-gnu/libglut.so
OpenGL_01: /usr/lib/x86_64-linux-gnu/libXmu.so
OpenGL_01: /usr/lib/x86_64-linux-gnu/libXi.so
OpenGL_01: CMakeFiles/OpenGL_01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenGL_01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGL_01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGL_01.dir/build: OpenGL_01

.PHONY : CMakeFiles/OpenGL_01.dir/build

CMakeFiles/OpenGL_01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGL_01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGL_01.dir/clean

CMakeFiles/OpenGL_01.dir/depend:
	cd /home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vladpc/GraphicsHW/HW1_Fireworks /home/vladpc/GraphicsHW/HW1_Fireworks /home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug /home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug /home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug/CMakeFiles/OpenGL_01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGL_01.dir/depend

