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
CMAKE_SOURCE_DIR = "/home/vladpc/Git Repositories/GraphicsHW/testApp"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/vladpc/Git Repositories/GraphicsHW/testApp/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/testApp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testApp.dir/flags.make

CMakeFiles/testApp.dir/main.cpp.o: CMakeFiles/testApp.dir/flags.make
CMakeFiles/testApp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vladpc/Git Repositories/GraphicsHW/testApp/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testApp.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testApp.dir/main.cpp.o -c "/home/vladpc/Git Repositories/GraphicsHW/testApp/main.cpp"

CMakeFiles/testApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testApp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vladpc/Git Repositories/GraphicsHW/testApp/main.cpp" > CMakeFiles/testApp.dir/main.cpp.i

CMakeFiles/testApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testApp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vladpc/Git Repositories/GraphicsHW/testApp/main.cpp" -o CMakeFiles/testApp.dir/main.cpp.s

# Object files for target testApp
testApp_OBJECTS = \
"CMakeFiles/testApp.dir/main.cpp.o"

# External object files for target testApp
testApp_EXTERNAL_OBJECTS =

testApp: CMakeFiles/testApp.dir/main.cpp.o
testApp: CMakeFiles/testApp.dir/build.make
testApp: CMakeFiles/testApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vladpc/Git Repositories/GraphicsHW/testApp/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testApp.dir/build: testApp

.PHONY : CMakeFiles/testApp.dir/build

CMakeFiles/testApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testApp.dir/clean

CMakeFiles/testApp.dir/depend:
	cd "/home/vladpc/Git Repositories/GraphicsHW/testApp/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vladpc/Git Repositories/GraphicsHW/testApp" "/home/vladpc/Git Repositories/GraphicsHW/testApp" "/home/vladpc/Git Repositories/GraphicsHW/testApp/cmake-build-debug" "/home/vladpc/Git Repositories/GraphicsHW/testApp/cmake-build-debug" "/home/vladpc/Git Repositories/GraphicsHW/testApp/cmake-build-debug/CMakeFiles/testApp.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/testApp.dir/depend

