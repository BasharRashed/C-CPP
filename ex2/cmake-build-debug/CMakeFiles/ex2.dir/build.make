# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/bashar/CLionProjects/ex2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ex2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ex2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex2.dir/flags.make

CMakeFiles/ex2.dir/main.c.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/main.c.o: ../main.c
CMakeFiles/ex2.dir/main.c.o: CMakeFiles/ex2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ex2.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ex2.dir/main.c.o -MF CMakeFiles/ex2.dir/main.c.o.d -o CMakeFiles/ex2.dir/main.c.o -c /mnt/c/Users/bashar/CLionProjects/ex2/main.c

CMakeFiles/ex2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex2.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/bashar/CLionProjects/ex2/main.c > CMakeFiles/ex2.dir/main.c.i

CMakeFiles/ex2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex2.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/bashar/CLionProjects/ex2/main.c -o CMakeFiles/ex2.dir/main.c.s

CMakeFiles/ex2.dir/sort_bus_lines.c.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/sort_bus_lines.c.o: ../sort_bus_lines.c
CMakeFiles/ex2.dir/sort_bus_lines.c.o: CMakeFiles/ex2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ex2.dir/sort_bus_lines.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ex2.dir/sort_bus_lines.c.o -MF CMakeFiles/ex2.dir/sort_bus_lines.c.o.d -o CMakeFiles/ex2.dir/sort_bus_lines.c.o -c /mnt/c/Users/bashar/CLionProjects/ex2/sort_bus_lines.c

CMakeFiles/ex2.dir/sort_bus_lines.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex2.dir/sort_bus_lines.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/bashar/CLionProjects/ex2/sort_bus_lines.c > CMakeFiles/ex2.dir/sort_bus_lines.c.i

CMakeFiles/ex2.dir/sort_bus_lines.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex2.dir/sort_bus_lines.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/bashar/CLionProjects/ex2/sort_bus_lines.c -o CMakeFiles/ex2.dir/sort_bus_lines.c.s

CMakeFiles/ex2.dir/test_bus_lines.c.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/test_bus_lines.c.o: ../test_bus_lines.c
CMakeFiles/ex2.dir/test_bus_lines.c.o: CMakeFiles/ex2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ex2.dir/test_bus_lines.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ex2.dir/test_bus_lines.c.o -MF CMakeFiles/ex2.dir/test_bus_lines.c.o.d -o CMakeFiles/ex2.dir/test_bus_lines.c.o -c /mnt/c/Users/bashar/CLionProjects/ex2/test_bus_lines.c

CMakeFiles/ex2.dir/test_bus_lines.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex2.dir/test_bus_lines.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/bashar/CLionProjects/ex2/test_bus_lines.c > CMakeFiles/ex2.dir/test_bus_lines.c.i

CMakeFiles/ex2.dir/test_bus_lines.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex2.dir/test_bus_lines.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/bashar/CLionProjects/ex2/test_bus_lines.c -o CMakeFiles/ex2.dir/test_bus_lines.c.s

# Object files for target ex2
ex2_OBJECTS = \
"CMakeFiles/ex2.dir/main.c.o" \
"CMakeFiles/ex2.dir/sort_bus_lines.c.o" \
"CMakeFiles/ex2.dir/test_bus_lines.c.o"

# External object files for target ex2
ex2_EXTERNAL_OBJECTS =

ex2: CMakeFiles/ex2.dir/main.c.o
ex2: CMakeFiles/ex2.dir/sort_bus_lines.c.o
ex2: CMakeFiles/ex2.dir/test_bus_lines.c.o
ex2: CMakeFiles/ex2.dir/build.make
ex2: CMakeFiles/ex2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ex2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex2.dir/build: ex2
.PHONY : CMakeFiles/ex2.dir/build

CMakeFiles/ex2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex2.dir/clean

CMakeFiles/ex2.dir/depend:
	cd /mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/bashar/CLionProjects/ex2 /mnt/c/Users/bashar/CLionProjects/ex2 /mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug /mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug /mnt/c/Users/bashar/CLionProjects/ex2/cmake-build-debug/CMakeFiles/ex2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex2.dir/depend

