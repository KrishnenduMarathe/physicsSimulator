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
CMAKE_SOURCE_DIR = /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build

# Include any dependencies generated for this target.
include CMakeFiles/physicsSimulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/physicsSimulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/physicsSimulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/physicsSimulator.dir/flags.make

CMakeFiles/physicsSimulator.dir/src/main.cpp.o: CMakeFiles/physicsSimulator.dir/flags.make
CMakeFiles/physicsSimulator.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/physicsSimulator.dir/src/main.cpp.o: CMakeFiles/physicsSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/physicsSimulator.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/physicsSimulator.dir/src/main.cpp.o -MF CMakeFiles/physicsSimulator.dir/src/main.cpp.o.d -o CMakeFiles/physicsSimulator.dir/src/main.cpp.o -c /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/src/main.cpp

CMakeFiles/physicsSimulator.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/physicsSimulator.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/src/main.cpp > CMakeFiles/physicsSimulator.dir/src/main.cpp.i

CMakeFiles/physicsSimulator.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/physicsSimulator.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/src/main.cpp -o CMakeFiles/physicsSimulator.dir/src/main.cpp.s

CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o: CMakeFiles/physicsSimulator.dir/flags.make
CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o: ../src/PhysicsEngine.cpp
CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o: CMakeFiles/physicsSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o -MF CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o.d -o CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o -c /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/src/PhysicsEngine.cpp

CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/src/PhysicsEngine.cpp > CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.i

CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/src/PhysicsEngine.cpp -o CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.s

# Object files for target physicsSimulator
physicsSimulator_OBJECTS = \
"CMakeFiles/physicsSimulator.dir/src/main.cpp.o" \
"CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o"

# External object files for target physicsSimulator
physicsSimulator_EXTERNAL_OBJECTS =

../physicsSimulator: CMakeFiles/physicsSimulator.dir/src/main.cpp.o
../physicsSimulator: CMakeFiles/physicsSimulator.dir/src/PhysicsEngine.cpp.o
../physicsSimulator: CMakeFiles/physicsSimulator.dir/build.make
../physicsSimulator: CMakeFiles/physicsSimulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../physicsSimulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/physicsSimulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/physicsSimulator.dir/build: ../physicsSimulator
.PHONY : CMakeFiles/physicsSimulator.dir/build

CMakeFiles/physicsSimulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/physicsSimulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/physicsSimulator.dir/clean

CMakeFiles/physicsSimulator.dir/depend:
	cd /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build /home/krishnendu/HardDrive/1_Projects/YouTube/physicsSimulator/build/CMakeFiles/physicsSimulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/physicsSimulator.dir/depend
