# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.23.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.23.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6"

# Include any dependencies generated for this target.
include CMakeFiles/simpleComputer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/simpleComputer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/simpleComputer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simpleComputer.dir/flags.make

CMakeFiles/simpleComputer.dir/memory.c.o: CMakeFiles/simpleComputer.dir/flags.make
CMakeFiles/simpleComputer.dir/memory.c.o: memory.c
CMakeFiles/simpleComputer.dir/memory.c.o: CMakeFiles/simpleComputer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/simpleComputer.dir/memory.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/simpleComputer.dir/memory.c.o -MF CMakeFiles/simpleComputer.dir/memory.c.o.d -o CMakeFiles/simpleComputer.dir/memory.c.o -c "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/memory.c"

CMakeFiles/simpleComputer.dir/memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simpleComputer.dir/memory.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/memory.c" > CMakeFiles/simpleComputer.dir/memory.c.i

CMakeFiles/simpleComputer.dir/memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simpleComputer.dir/memory.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/memory.c" -o CMakeFiles/simpleComputer.dir/memory.c.s

CMakeFiles/simpleComputer.dir/register.c.o: CMakeFiles/simpleComputer.dir/flags.make
CMakeFiles/simpleComputer.dir/register.c.o: register.c
CMakeFiles/simpleComputer.dir/register.c.o: CMakeFiles/simpleComputer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/simpleComputer.dir/register.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/simpleComputer.dir/register.c.o -MF CMakeFiles/simpleComputer.dir/register.c.o.d -o CMakeFiles/simpleComputer.dir/register.c.o -c "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/register.c"

CMakeFiles/simpleComputer.dir/register.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simpleComputer.dir/register.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/register.c" > CMakeFiles/simpleComputer.dir/register.c.i

CMakeFiles/simpleComputer.dir/register.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simpleComputer.dir/register.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/register.c" -o CMakeFiles/simpleComputer.dir/register.c.s

# Object files for target simpleComputer
simpleComputer_OBJECTS = \
"CMakeFiles/simpleComputer.dir/memory.c.o" \
"CMakeFiles/simpleComputer.dir/register.c.o"

# External object files for target simpleComputer
simpleComputer_EXTERNAL_OBJECTS =

libsimpleComputer.a: CMakeFiles/simpleComputer.dir/memory.c.o
libsimpleComputer.a: CMakeFiles/simpleComputer.dir/register.c.o
libsimpleComputer.a: CMakeFiles/simpleComputer.dir/build.make
libsimpleComputer.a: CMakeFiles/simpleComputer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libsimpleComputer.a"
	$(CMAKE_COMMAND) -P CMakeFiles/simpleComputer.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simpleComputer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simpleComputer.dir/build: libsimpleComputer.a
.PHONY : CMakeFiles/simpleComputer.dir/build

CMakeFiles/simpleComputer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simpleComputer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simpleComputer.dir/clean

CMakeFiles/simpleComputer.dir/depend:
	cd "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6" "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6" "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6" "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6" "/Users/defaultid/Google Drive/учоба/4 семестр/АЭВМ/6/CMakeFiles/simpleComputer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/simpleComputer.dir/depend

