# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/cmake/340/bin/cmake

# The command to remove a file.
RM = /snap/cmake/340/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01

# Include any dependencies generated for this target.
include CMakeFiles/mytest1_glfw.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mytest1_glfw.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mytest1_glfw.dir/flags.make

CMakeFiles/mytest1_glfw.dir/main.o: CMakeFiles/mytest1_glfw.dir/flags.make
CMakeFiles/mytest1_glfw.dir/main.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mytest1_glfw.dir/main.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytest1_glfw.dir/main.o -c /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01/main.cpp

CMakeFiles/mytest1_glfw.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytest1_glfw.dir/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01/main.cpp > CMakeFiles/mytest1_glfw.dir/main.i

CMakeFiles/mytest1_glfw.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytest1_glfw.dir/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01/main.cpp -o CMakeFiles/mytest1_glfw.dir/main.s

# Object files for target mytest1_glfw
mytest1_glfw_OBJECTS = \
"CMakeFiles/mytest1_glfw.dir/main.o"

# External object files for target mytest1_glfw
mytest1_glfw_EXTERNAL_OBJECTS =

mytest1_glfw: CMakeFiles/mytest1_glfw.dir/main.o
mytest1_glfw: CMakeFiles/mytest1_glfw.dir/build.make
mytest1_glfw: /usr/lib/x86_64-linux-gnu/libGL.so
mytest1_glfw: /usr/lib/x86_64-linux-gnu/libGLU.so
mytest1_glfw: CMakeFiles/mytest1_glfw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mytest1_glfw"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mytest1_glfw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mytest1_glfw.dir/build: mytest1_glfw

.PHONY : CMakeFiles/mytest1_glfw.dir/build

CMakeFiles/mytest1_glfw.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mytest1_glfw.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mytest1_glfw.dir/clean

CMakeFiles/mytest1_glfw.dir/depend:
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01 /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01 /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01 /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01 /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Tutorial_01/CMakeFiles/mytest1_glfw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mytest1_glfw.dir/depend
