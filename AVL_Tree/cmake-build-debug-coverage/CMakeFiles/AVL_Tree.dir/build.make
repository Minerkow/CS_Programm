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
CMAKE_COMMAND = /home/minerkow/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/minerkow/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage"

# Include any dependencies generated for this target.
include CMakeFiles/AVL_Tree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AVL_Tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AVL_Tree.dir/flags.make

CMakeFiles/AVL_Tree.dir/main.c.o: CMakeFiles/AVL_Tree.dir/flags.make
CMakeFiles/AVL_Tree.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/AVL_Tree.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/AVL_Tree.dir/main.c.o   -c "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/main.c"

CMakeFiles/AVL_Tree.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/AVL_Tree.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/main.c" > CMakeFiles/AVL_Tree.dir/main.c.i

CMakeFiles/AVL_Tree.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/AVL_Tree.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/main.c" -o CMakeFiles/AVL_Tree.dir/main.c.s

CMakeFiles/AVL_Tree.dir/AVL_Tree.c.o: CMakeFiles/AVL_Tree.dir/flags.make
CMakeFiles/AVL_Tree.dir/AVL_Tree.c.o: ../AVL_Tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/AVL_Tree.dir/AVL_Tree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/AVL_Tree.dir/AVL_Tree.c.o   -c "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/AVL_Tree.c"

CMakeFiles/AVL_Tree.dir/AVL_Tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/AVL_Tree.dir/AVL_Tree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/AVL_Tree.c" > CMakeFiles/AVL_Tree.dir/AVL_Tree.c.i

CMakeFiles/AVL_Tree.dir/AVL_Tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/AVL_Tree.dir/AVL_Tree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/AVL_Tree.c" -o CMakeFiles/AVL_Tree.dir/AVL_Tree.c.s

CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.o: CMakeFiles/AVL_Tree.dir/flags.make
CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.o: ../AVL_Iterator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.o   -c "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/AVL_Iterator.c"

CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/AVL_Iterator.c" > CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.i

CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/AVL_Iterator.c" -o CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.s

# Object files for target AVL_Tree
AVL_Tree_OBJECTS = \
"CMakeFiles/AVL_Tree.dir/main.c.o" \
"CMakeFiles/AVL_Tree.dir/AVL_Tree.c.o" \
"CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.o"

# External object files for target AVL_Tree
AVL_Tree_EXTERNAL_OBJECTS =

AVL_Tree: CMakeFiles/AVL_Tree.dir/main.c.o
AVL_Tree: CMakeFiles/AVL_Tree.dir/AVL_Tree.c.o
AVL_Tree: CMakeFiles/AVL_Tree.dir/AVL_Iterator.c.o
AVL_Tree: CMakeFiles/AVL_Tree.dir/build.make
AVL_Tree: CMakeFiles/AVL_Tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable AVL_Tree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AVL_Tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AVL_Tree.dir/build: AVL_Tree

.PHONY : CMakeFiles/AVL_Tree.dir/build

CMakeFiles/AVL_Tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AVL_Tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AVL_Tree.dir/clean

CMakeFiles/AVL_Tree.dir/depend:
	cd "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree" "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree" "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage" "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage" "/home/minerkow/Рабочий стол/CS_Programm/AVL_Tree/cmake-build-debug-coverage/CMakeFiles/AVL_Tree.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/AVL_Tree.dir/depend

