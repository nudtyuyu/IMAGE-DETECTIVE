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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/GUI/jpeg2-6b

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/GUI/jpeg2-6b/build

# Include any dependencies generated for this target.
include sharedlib/CMakeFiles/jpegtran.dir/depend.make

# Include the progress variables for this target.
include sharedlib/CMakeFiles/jpegtran.dir/progress.make

# Include the compile flags for this target's objects.
include sharedlib/CMakeFiles/jpegtran.dir/flags.make

sharedlib/CMakeFiles/jpegtran.dir/__/jpegtran.c.o: sharedlib/CMakeFiles/jpegtran.dir/flags.make
sharedlib/CMakeFiles/jpegtran.dir/__/jpegtran.c.o: ../jpegtran.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/GUI/jpeg2-6b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object sharedlib/CMakeFiles/jpegtran.dir/__/jpegtran.c.o"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jpegtran.dir/__/jpegtran.c.o   -c /root/GUI/jpeg2-6b/jpegtran.c

sharedlib/CMakeFiles/jpegtran.dir/__/jpegtran.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jpegtran.dir/__/jpegtran.c.i"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/GUI/jpeg2-6b/jpegtran.c > CMakeFiles/jpegtran.dir/__/jpegtran.c.i

sharedlib/CMakeFiles/jpegtran.dir/__/jpegtran.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jpegtran.dir/__/jpegtran.c.s"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/GUI/jpeg2-6b/jpegtran.c -o CMakeFiles/jpegtran.dir/__/jpegtran.c.s

sharedlib/CMakeFiles/jpegtran.dir/__/cdjpeg.c.o: sharedlib/CMakeFiles/jpegtran.dir/flags.make
sharedlib/CMakeFiles/jpegtran.dir/__/cdjpeg.c.o: ../cdjpeg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/GUI/jpeg2-6b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object sharedlib/CMakeFiles/jpegtran.dir/__/cdjpeg.c.o"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jpegtran.dir/__/cdjpeg.c.o   -c /root/GUI/jpeg2-6b/cdjpeg.c

sharedlib/CMakeFiles/jpegtran.dir/__/cdjpeg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jpegtran.dir/__/cdjpeg.c.i"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/GUI/jpeg2-6b/cdjpeg.c > CMakeFiles/jpegtran.dir/__/cdjpeg.c.i

sharedlib/CMakeFiles/jpegtran.dir/__/cdjpeg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jpegtran.dir/__/cdjpeg.c.s"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/GUI/jpeg2-6b/cdjpeg.c -o CMakeFiles/jpegtran.dir/__/cdjpeg.c.s

sharedlib/CMakeFiles/jpegtran.dir/__/rdswitch.c.o: sharedlib/CMakeFiles/jpegtran.dir/flags.make
sharedlib/CMakeFiles/jpegtran.dir/__/rdswitch.c.o: ../rdswitch.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/GUI/jpeg2-6b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object sharedlib/CMakeFiles/jpegtran.dir/__/rdswitch.c.o"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jpegtran.dir/__/rdswitch.c.o   -c /root/GUI/jpeg2-6b/rdswitch.c

sharedlib/CMakeFiles/jpegtran.dir/__/rdswitch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jpegtran.dir/__/rdswitch.c.i"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/GUI/jpeg2-6b/rdswitch.c > CMakeFiles/jpegtran.dir/__/rdswitch.c.i

sharedlib/CMakeFiles/jpegtran.dir/__/rdswitch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jpegtran.dir/__/rdswitch.c.s"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/GUI/jpeg2-6b/rdswitch.c -o CMakeFiles/jpegtran.dir/__/rdswitch.c.s

sharedlib/CMakeFiles/jpegtran.dir/__/transupp.c.o: sharedlib/CMakeFiles/jpegtran.dir/flags.make
sharedlib/CMakeFiles/jpegtran.dir/__/transupp.c.o: ../transupp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/GUI/jpeg2-6b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object sharedlib/CMakeFiles/jpegtran.dir/__/transupp.c.o"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jpegtran.dir/__/transupp.c.o   -c /root/GUI/jpeg2-6b/transupp.c

sharedlib/CMakeFiles/jpegtran.dir/__/transupp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jpegtran.dir/__/transupp.c.i"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/GUI/jpeg2-6b/transupp.c > CMakeFiles/jpegtran.dir/__/transupp.c.i

sharedlib/CMakeFiles/jpegtran.dir/__/transupp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jpegtran.dir/__/transupp.c.s"
	cd /root/GUI/jpeg2-6b/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/GUI/jpeg2-6b/transupp.c -o CMakeFiles/jpegtran.dir/__/transupp.c.s

# Object files for target jpegtran
jpegtran_OBJECTS = \
"CMakeFiles/jpegtran.dir/__/jpegtran.c.o" \
"CMakeFiles/jpegtran.dir/__/cdjpeg.c.o" \
"CMakeFiles/jpegtran.dir/__/rdswitch.c.o" \
"CMakeFiles/jpegtran.dir/__/transupp.c.o"

# External object files for target jpegtran
jpegtran_EXTERNAL_OBJECTS =

jpegtran: sharedlib/CMakeFiles/jpegtran.dir/__/jpegtran.c.o
jpegtran: sharedlib/CMakeFiles/jpegtran.dir/__/cdjpeg.c.o
jpegtran: sharedlib/CMakeFiles/jpegtran.dir/__/rdswitch.c.o
jpegtran: sharedlib/CMakeFiles/jpegtran.dir/__/transupp.c.o
jpegtran: sharedlib/CMakeFiles/jpegtran.dir/build.make
jpegtran: libjpeg.so.62.3.0
jpegtran: sharedlib/CMakeFiles/jpegtran.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/GUI/jpeg2-6b/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../jpegtran"
	cd /root/GUI/jpeg2-6b/build/sharedlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jpegtran.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sharedlib/CMakeFiles/jpegtran.dir/build: jpegtran

.PHONY : sharedlib/CMakeFiles/jpegtran.dir/build

sharedlib/CMakeFiles/jpegtran.dir/clean:
	cd /root/GUI/jpeg2-6b/build/sharedlib && $(CMAKE_COMMAND) -P CMakeFiles/jpegtran.dir/cmake_clean.cmake
.PHONY : sharedlib/CMakeFiles/jpegtran.dir/clean

sharedlib/CMakeFiles/jpegtran.dir/depend:
	cd /root/GUI/jpeg2-6b/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/GUI/jpeg2-6b /root/GUI/jpeg2-6b/sharedlib /root/GUI/jpeg2-6b/build /root/GUI/jpeg2-6b/build/sharedlib /root/GUI/jpeg2-6b/build/sharedlib/CMakeFiles/jpegtran.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sharedlib/CMakeFiles/jpegtran.dir/depend

