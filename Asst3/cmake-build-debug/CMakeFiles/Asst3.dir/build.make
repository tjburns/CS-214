# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Asst3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Asst3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Asst3.dir/flags.make

CMakeFiles/Asst3.dir/readInput.c.obj: CMakeFiles/Asst3.dir/flags.make
CMakeFiles/Asst3.dir/readInput.c.obj: ../readInput.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Asst3.dir/readInput.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Asst3.dir\readInput.c.obj   -c "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\readInput.c"

CMakeFiles/Asst3.dir/readInput.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Asst3.dir/readInput.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\readInput.c" > CMakeFiles\Asst3.dir\readInput.c.i

CMakeFiles/Asst3.dir/readInput.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Asst3.dir/readInput.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\readInput.c" -o CMakeFiles\Asst3.dir\readInput.c.s

# Object files for target Asst3
Asst3_OBJECTS = \
"CMakeFiles/Asst3.dir/readInput.c.obj"

# External object files for target Asst3
Asst3_EXTERNAL_OBJECTS =

Asst3.exe: CMakeFiles/Asst3.dir/readInput.c.obj
Asst3.exe: CMakeFiles/Asst3.dir/build.make
Asst3.exe: CMakeFiles/Asst3.dir/linklibs.rsp
Asst3.exe: CMakeFiles/Asst3.dir/objects1.rsp
Asst3.exe: CMakeFiles/Asst3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Asst3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Asst3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Asst3.dir/build: Asst3.exe

.PHONY : CMakeFiles/Asst3.dir/build

CMakeFiles/Asst3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Asst3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Asst3.dir/clean

CMakeFiles/Asst3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3" "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3" "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\cmake-build-debug" "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\cmake-build-debug" "C:\Users\tjbur\Google Drive\College\Spring 2019\CS 214\Asst3\cmake-build-debug\CMakeFiles\Asst3.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Asst3.dir/depend

