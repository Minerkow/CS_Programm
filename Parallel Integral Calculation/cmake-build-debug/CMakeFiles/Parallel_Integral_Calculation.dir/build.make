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
CMAKE_SOURCE_DIR = "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Parallel_Integral_Calculation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Parallel_Integral_Calculation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Parallel_Integral_Calculation.dir/flags.make

CMakeFiles/Parallel_Integral_Calculation.dir/main.c.o: CMakeFiles/Parallel_Integral_Calculation.dir/flags.make
CMakeFiles/Parallel_Integral_Calculation.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Parallel_Integral_Calculation.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Parallel_Integral_Calculation.dir/main.c.o   -c "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/main.c"

CMakeFiles/Parallel_Integral_Calculation.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Parallel_Integral_Calculation.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/main.c" > CMakeFiles/Parallel_Integral_Calculation.dir/main.c.i

CMakeFiles/Parallel_Integral_Calculation.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Parallel_Integral_Calculation.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/main.c" -o CMakeFiles/Parallel_Integral_Calculation.dir/main.c.s

# Object files for target Parallel_Integral_Calculation
Parallel_Integral_Calculation_OBJECTS = \
"CMakeFiles/Parallel_Integral_Calculation.dir/main.c.o"

# External object files for target Parallel_Integral_Calculation
Parallel_Integral_Calculation_EXTERNAL_OBJECTS =

Parallel_Integral_Calculation: CMakeFiles/Parallel_Integral_Calculation.dir/main.c.o
Parallel_Integral_Calculation: CMakeFiles/Parallel_Integral_Calculation.dir/build.make
Parallel_Integral_Calculation: CMakeFiles/Parallel_Integral_Calculation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Parallel_Integral_Calculation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Parallel_Integral_Calculation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Parallel_Integral_Calculation.dir/build: Parallel_Integral_Calculation

.PHONY : CMakeFiles/Parallel_Integral_Calculation.dir/build

CMakeFiles/Parallel_Integral_Calculation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Parallel_Integral_Calculation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Parallel_Integral_Calculation.dir/clean

CMakeFiles/Parallel_Integral_Calculation.dir/depend:
	cd "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation" "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation" "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/cmake-build-debug" "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/cmake-build-debug" "/home/minerkow/Рабочий стол/CS_Programm/Parallel Integral Calculation/cmake-build-debug/CMakeFiles/Parallel_Integral_Calculation.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Parallel_Integral_Calculation.dir/depend

