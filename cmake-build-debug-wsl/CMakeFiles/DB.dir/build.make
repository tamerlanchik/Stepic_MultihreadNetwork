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
include CMakeFiles/DB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DB.dir/flags.make

CMakeFiles/DB.dir/main.cpp.o: CMakeFiles/DB.dir/flags.make
CMakeFiles/DB.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DB.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DB.dir/main.cpp.o -c /mnt/c/Users/Ian/Documents/Programming/TPark/DB/main.cpp

CMakeFiles/DB.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DB.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ian/Documents/Programming/TPark/DB/main.cpp > CMakeFiles/DB.dir/main.cpp.i

CMakeFiles/DB.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DB.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ian/Documents/Programming/TPark/DB/main.cpp -o CMakeFiles/DB.dir/main.cpp.s

CMakeFiles/DB.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/DB.dir/main.cpp.o.requires

CMakeFiles/DB.dir/main.cpp.o.provides: CMakeFiles/DB.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/DB.dir/build.make CMakeFiles/DB.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/DB.dir/main.cpp.o.provides

CMakeFiles/DB.dir/main.cpp.o.provides.build: CMakeFiles/DB.dir/main.cpp.o


CMakeFiles/DB.dir/multiplex/select.cpp.o: CMakeFiles/DB.dir/flags.make
CMakeFiles/DB.dir/multiplex/select.cpp.o: ../multiplex/select.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DB.dir/multiplex/select.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DB.dir/multiplex/select.cpp.o -c /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/select.cpp

CMakeFiles/DB.dir/multiplex/select.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DB.dir/multiplex/select.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/select.cpp > CMakeFiles/DB.dir/multiplex/select.cpp.i

CMakeFiles/DB.dir/multiplex/select.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DB.dir/multiplex/select.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/select.cpp -o CMakeFiles/DB.dir/multiplex/select.cpp.s

CMakeFiles/DB.dir/multiplex/select.cpp.o.requires:

.PHONY : CMakeFiles/DB.dir/multiplex/select.cpp.o.requires

CMakeFiles/DB.dir/multiplex/select.cpp.o.provides: CMakeFiles/DB.dir/multiplex/select.cpp.o.requires
	$(MAKE) -f CMakeFiles/DB.dir/build.make CMakeFiles/DB.dir/multiplex/select.cpp.o.provides.build
.PHONY : CMakeFiles/DB.dir/multiplex/select.cpp.o.provides

CMakeFiles/DB.dir/multiplex/select.cpp.o.provides.build: CMakeFiles/DB.dir/multiplex/select.cpp.o


CMakeFiles/DB.dir/multiplex/poll.cpp.o: CMakeFiles/DB.dir/flags.make
CMakeFiles/DB.dir/multiplex/poll.cpp.o: ../multiplex/poll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DB.dir/multiplex/poll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DB.dir/multiplex/poll.cpp.o -c /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/poll.cpp

CMakeFiles/DB.dir/multiplex/poll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DB.dir/multiplex/poll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/poll.cpp > CMakeFiles/DB.dir/multiplex/poll.cpp.i

CMakeFiles/DB.dir/multiplex/poll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DB.dir/multiplex/poll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/poll.cpp -o CMakeFiles/DB.dir/multiplex/poll.cpp.s

CMakeFiles/DB.dir/multiplex/poll.cpp.o.requires:

.PHONY : CMakeFiles/DB.dir/multiplex/poll.cpp.o.requires

CMakeFiles/DB.dir/multiplex/poll.cpp.o.provides: CMakeFiles/DB.dir/multiplex/poll.cpp.o.requires
	$(MAKE) -f CMakeFiles/DB.dir/build.make CMakeFiles/DB.dir/multiplex/poll.cpp.o.provides.build
.PHONY : CMakeFiles/DB.dir/multiplex/poll.cpp.o.provides

CMakeFiles/DB.dir/multiplex/poll.cpp.o.provides.build: CMakeFiles/DB.dir/multiplex/poll.cpp.o


CMakeFiles/DB.dir/multiplex/chat/server.cpp.o: CMakeFiles/DB.dir/flags.make
CMakeFiles/DB.dir/multiplex/chat/server.cpp.o: ../multiplex/chat/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DB.dir/multiplex/chat/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DB.dir/multiplex/chat/server.cpp.o -c /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/server.cpp

CMakeFiles/DB.dir/multiplex/chat/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DB.dir/multiplex/chat/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/server.cpp > CMakeFiles/DB.dir/multiplex/chat/server.cpp.i

CMakeFiles/DB.dir/multiplex/chat/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DB.dir/multiplex/chat/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/server.cpp -o CMakeFiles/DB.dir/multiplex/chat/server.cpp.s

CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.requires:

.PHONY : CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.requires

CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.provides: CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.requires
	$(MAKE) -f CMakeFiles/DB.dir/build.make CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.provides.build
.PHONY : CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.provides

CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.provides.build: CMakeFiles/DB.dir/multiplex/chat/server.cpp.o


CMakeFiles/DB.dir/multiplex/chat/client.cpp.o: CMakeFiles/DB.dir/flags.make
CMakeFiles/DB.dir/multiplex/chat/client.cpp.o: ../multiplex/chat/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/DB.dir/multiplex/chat/client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DB.dir/multiplex/chat/client.cpp.o -c /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/client.cpp

CMakeFiles/DB.dir/multiplex/chat/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DB.dir/multiplex/chat/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/client.cpp > CMakeFiles/DB.dir/multiplex/chat/client.cpp.i

CMakeFiles/DB.dir/multiplex/chat/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DB.dir/multiplex/chat/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ian/Documents/Programming/TPark/DB/multiplex/chat/client.cpp -o CMakeFiles/DB.dir/multiplex/chat/client.cpp.s

CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.requires:

.PHONY : CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.requires

CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.provides: CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.requires
	$(MAKE) -f CMakeFiles/DB.dir/build.make CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.provides.build
.PHONY : CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.provides

CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.provides.build: CMakeFiles/DB.dir/multiplex/chat/client.cpp.o


# Object files for target DB
DB_OBJECTS = \
"CMakeFiles/DB.dir/main.cpp.o" \
"CMakeFiles/DB.dir/multiplex/select.cpp.o" \
"CMakeFiles/DB.dir/multiplex/poll.cpp.o" \
"CMakeFiles/DB.dir/multiplex/chat/server.cpp.o" \
"CMakeFiles/DB.dir/multiplex/chat/client.cpp.o"

# External object files for target DB
DB_EXTERNAL_OBJECTS =

DB: CMakeFiles/DB.dir/main.cpp.o
DB: CMakeFiles/DB.dir/multiplex/select.cpp.o
DB: CMakeFiles/DB.dir/multiplex/poll.cpp.o
DB: CMakeFiles/DB.dir/multiplex/chat/server.cpp.o
DB: CMakeFiles/DB.dir/multiplex/chat/client.cpp.o
DB: CMakeFiles/DB.dir/build.make
DB: CMakeFiles/DB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable DB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DB.dir/build: DB

.PHONY : CMakeFiles/DB.dir/build

CMakeFiles/DB.dir/requires: CMakeFiles/DB.dir/main.cpp.o.requires
CMakeFiles/DB.dir/requires: CMakeFiles/DB.dir/multiplex/select.cpp.o.requires
CMakeFiles/DB.dir/requires: CMakeFiles/DB.dir/multiplex/poll.cpp.o.requires
CMakeFiles/DB.dir/requires: CMakeFiles/DB.dir/multiplex/chat/server.cpp.o.requires
CMakeFiles/DB.dir/requires: CMakeFiles/DB.dir/multiplex/chat/client.cpp.o.requires

.PHONY : CMakeFiles/DB.dir/requires

CMakeFiles/DB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DB.dir/clean

CMakeFiles/DB.dir/depend:
	cd /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Ian/Documents/Programming/TPark/DB /mnt/c/Users/Ian/Documents/Programming/TPark/DB /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl /mnt/c/Users/Ian/Documents/Programming/TPark/DB/cmake-build-debug-wsl/CMakeFiles/DB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DB.dir/depend
