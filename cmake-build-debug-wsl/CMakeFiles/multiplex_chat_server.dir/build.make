# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Ian/Documents/Programming/TPark/DB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl

# Include any dependencies generated for this target.
include CMakeFiles/multiplex_chat_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multiplex_chat_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multiplex_chat_server.dir/flags.make

CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o: CMakeFiles/multiplex_chat_server.dir/flags.make
CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o: ../multiplex/chat/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o -c /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/server.cpp

CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/server.cpp > CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.i

CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/server.cpp -o CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.s

CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.requires:

.PHONY : CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.requires

CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.provides: CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.requires
	$(MAKE) -f CMakeFiles/multiplex_chat_server.dir/build.make CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.provides.build
.PHONY : CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.provides

CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.provides.build: CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o


# Object files for target multiplex_chat_server
multiplex_chat_server_OBJECTS = \
"CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o"

# External object files for target multiplex_chat_server
multiplex_chat_server_EXTERNAL_OBJECTS =

multiplex_chat_server: CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o
multiplex_chat_server: CMakeFiles/multiplex_chat_server.dir/build.make
multiplex_chat_server: CMakeFiles/multiplex_chat_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable multiplex_chat_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multiplex_chat_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multiplex_chat_server.dir/build: multiplex_chat_server

.PHONY : CMakeFiles/multiplex_chat_server.dir/build

CMakeFiles/multiplex_chat_server.dir/requires: CMakeFiles/multiplex_chat_server.dir/multiplex/chat/server.cpp.o.requires

.PHONY : CMakeFiles/multiplex_chat_server.dir/requires

CMakeFiles/multiplex_chat_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multiplex_chat_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multiplex_chat_server.dir/clean

CMakeFiles/multiplex_chat_server.dir/depend:
	cd /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Ian/Documents/Programming/TPark/DB /mnt/c/Users/Ian/Documents/Programming/TPark/DB /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles/multiplex_chat_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multiplex_chat_server.dir/depend
