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
CMAKE_COMMAND = /snap/cmake/372/bin/cmake

# The command to remove a file.
RM = /snap/cmake/372/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux

# Include any dependencies generated for this target.
include src/mytest1_glut/CMakeFiles/mytest1_glut.dir/depend.make

# Include the progress variables for this target.
include src/mytest1_glut/CMakeFiles/mytest1_glut.dir/progress.make

# Include the compile flags for this target's objects.
include src/mytest1_glut/CMakeFiles/mytest1_glut.dir/flags.make

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.o: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/flags.make
src/mytest1_glut/CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.o: ../dep/include/glad/glad/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/mytest1_glut/CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.o"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.o   -c /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/dep/include/glad/glad/glad.c

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.i"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/dep/include/glad/glad/glad.c > CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.i

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.s"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/dep/include/glad/glad/glad.c -o CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.s

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.o: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/flags.make
src/mytest1_glut/CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.o: ../src/mytest1_glut/mytest1_glut.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/mytest1_glut/CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.o"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.o -c /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glut/mytest1_glut.cpp

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.i"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glut/mytest1_glut.cpp > CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.i

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.s"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glut/mytest1_glut.cpp -o CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.s

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/shaders.cpp.o: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/flags.make
src/mytest1_glut/CMakeFiles/mytest1_glut.dir/shaders.cpp.o: ../src/mytest1_glut/shaders.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/mytest1_glut/CMakeFiles/mytest1_glut.dir/shaders.cpp.o"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytest1_glut.dir/shaders.cpp.o -c /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glut/shaders.cpp

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytest1_glut.dir/shaders.cpp.i"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glut/shaders.cpp > CMakeFiles/mytest1_glut.dir/shaders.cpp.i

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytest1_glut.dir/shaders.cpp.s"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glut/shaders.cpp -o CMakeFiles/mytest1_glut.dir/shaders.cpp.s

# Object files for target mytest1_glut
mytest1_glut_OBJECTS = \
"CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.o" \
"CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.o" \
"CMakeFiles/mytest1_glut.dir/shaders.cpp.o"

# External object files for target mytest1_glut
mytest1_glut_EXTERNAL_OBJECTS =

src/mytest1_glut/mytest1_glut: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/__/__/dep/include/glad/glad/glad.c.o
src/mytest1_glut/mytest1_glut: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/mytest1_glut.cpp.o
src/mytest1_glut/mytest1_glut: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/shaders.cpp.o
src/mytest1_glut/mytest1_glut: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/build.make
src/mytest1_glut/mytest1_glut: /usr/lib/x86_64-linux-gnu/libGL.so
src/mytest1_glut/mytest1_glut: /usr/lib/x86_64-linux-gnu/libGLU.so
src/mytest1_glut/mytest1_glut: src/mytest1_glut/CMakeFiles/mytest1_glut.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mytest1_glut"
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mytest1_glut.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/mytest1_glut/CMakeFiles/mytest1_glut.dir/build: src/mytest1_glut/mytest1_glut

.PHONY : src/mytest1_glut/CMakeFiles/mytest1_glut.dir/build

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/clean:
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut && $(CMAKE_COMMAND) -P CMakeFiles/mytest1_glut.dir/cmake_clean.cmake
.PHONY : src/mytest1_glut/CMakeFiles/mytest1_glut.dir/clean

src/mytest1_glut/CMakeFiles/mytest1_glut.dir/depend:
	cd /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/src/mytest1_glut /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut /home/luis/Escritorio/GLFW_GLAD_GLUT_GLEW_cmake_project_Windows_Linux/GLFW_GLAD_GLUT_GLEW_cmake_project/build_linux/src/mytest1_glut/CMakeFiles/mytest1_glut.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/mytest1_glut/CMakeFiles/mytest1_glut.dir/depend

