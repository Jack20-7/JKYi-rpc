# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/admin/JKYi-rpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/admin/JKYi-rpc/build

# Include any dependencies generated for this target.
include examples/caller/CMakeFiles/consumer.dir/depend.make

# Include the progress variables for this target.
include examples/caller/CMakeFiles/consumer.dir/progress.make

# Include the compile flags for this target's objects.
include examples/caller/CMakeFiles/consumer.dir/flags.make

examples/caller/CMakeFiles/consumer.dir/callerfriendservice.cc.o: examples/caller/CMakeFiles/consumer.dir/flags.make
examples/caller/CMakeFiles/consumer.dir/callerfriendservice.cc.o: ../examples/caller/callerfriendservice.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admin/JKYi-rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/caller/CMakeFiles/consumer.dir/callerfriendservice.cc.o"
	cd /home/admin/JKYi-rpc/build/examples/caller && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/consumer.dir/callerfriendservice.cc.o -c /home/admin/JKYi-rpc/examples/caller/callerfriendservice.cc

examples/caller/CMakeFiles/consumer.dir/callerfriendservice.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/consumer.dir/callerfriendservice.cc.i"
	cd /home/admin/JKYi-rpc/build/examples/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/admin/JKYi-rpc/examples/caller/callerfriendservice.cc > CMakeFiles/consumer.dir/callerfriendservice.cc.i

examples/caller/CMakeFiles/consumer.dir/callerfriendservice.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/consumer.dir/callerfriendservice.cc.s"
	cd /home/admin/JKYi-rpc/build/examples/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/admin/JKYi-rpc/examples/caller/callerfriendservice.cc -o CMakeFiles/consumer.dir/callerfriendservice.cc.s

examples/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o: examples/caller/CMakeFiles/consumer.dir/flags.make
examples/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o: ../examples/friend.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admin/JKYi-rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o"
	cd /home/admin/JKYi-rpc/build/examples/caller && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/consumer.dir/__/friend.pb.cc.o -c /home/admin/JKYi-rpc/examples/friend.pb.cc

examples/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/consumer.dir/__/friend.pb.cc.i"
	cd /home/admin/JKYi-rpc/build/examples/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/admin/JKYi-rpc/examples/friend.pb.cc > CMakeFiles/consumer.dir/__/friend.pb.cc.i

examples/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/consumer.dir/__/friend.pb.cc.s"
	cd /home/admin/JKYi-rpc/build/examples/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/admin/JKYi-rpc/examples/friend.pb.cc -o CMakeFiles/consumer.dir/__/friend.pb.cc.s

# Object files for target consumer
consumer_OBJECTS = \
"CMakeFiles/consumer.dir/callerfriendservice.cc.o" \
"CMakeFiles/consumer.dir/__/friend.pb.cc.o"

# External object files for target consumer
consumer_EXTERNAL_OBJECTS =

../bin/consumer: examples/caller/CMakeFiles/consumer.dir/callerfriendservice.cc.o
../bin/consumer: examples/caller/CMakeFiles/consumer.dir/__/friend.pb.cc.o
../bin/consumer: examples/caller/CMakeFiles/consumer.dir/build.make
../bin/consumer: ../lib/libJKYiRpc.so
../bin/consumer: ../JKYi/lib/libJKYi.so
../bin/consumer: examples/caller/CMakeFiles/consumer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/admin/JKYi-rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../../bin/consumer"
	cd /home/admin/JKYi-rpc/build/examples/caller && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/consumer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/caller/CMakeFiles/consumer.dir/build: ../bin/consumer

.PHONY : examples/caller/CMakeFiles/consumer.dir/build

examples/caller/CMakeFiles/consumer.dir/clean:
	cd /home/admin/JKYi-rpc/build/examples/caller && $(CMAKE_COMMAND) -P CMakeFiles/consumer.dir/cmake_clean.cmake
.PHONY : examples/caller/CMakeFiles/consumer.dir/clean

examples/caller/CMakeFiles/consumer.dir/depend:
	cd /home/admin/JKYi-rpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/admin/JKYi-rpc /home/admin/JKYi-rpc/examples/caller /home/admin/JKYi-rpc/build /home/admin/JKYi-rpc/build/examples/caller /home/admin/JKYi-rpc/build/examples/caller/CMakeFiles/consumer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/caller/CMakeFiles/consumer.dir/depend

