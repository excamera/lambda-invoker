# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kvasukib/LambdaPerf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kvasukib/LambdaPerf/build

# Include any dependencies generated for this target.
include CMakeFiles/lambda-invoke.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lambda-invoke.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lambda-invoke.dir/flags.make

CMakeFiles/lambda-invoke.dir/src/main.cpp.o: CMakeFiles/lambda-invoke.dir/flags.make
CMakeFiles/lambda-invoke.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kvasukib/LambdaPerf/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lambda-invoke.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lambda-invoke.dir/src/main.cpp.o -c /home/kvasukib/LambdaPerf/src/main.cpp

CMakeFiles/lambda-invoke.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lambda-invoke.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kvasukib/LambdaPerf/src/main.cpp > CMakeFiles/lambda-invoke.dir/src/main.cpp.i

CMakeFiles/lambda-invoke.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lambda-invoke.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kvasukib/LambdaPerf/src/main.cpp -o CMakeFiles/lambda-invoke.dir/src/main.cpp.s

CMakeFiles/lambda-invoke.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/lambda-invoke.dir/src/main.cpp.o.requires

CMakeFiles/lambda-invoke.dir/src/main.cpp.o.provides: CMakeFiles/lambda-invoke.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/lambda-invoke.dir/build.make CMakeFiles/lambda-invoke.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/lambda-invoke.dir/src/main.cpp.o.provides

CMakeFiles/lambda-invoke.dir/src/main.cpp.o.provides.build: CMakeFiles/lambda-invoke.dir/src/main.cpp.o

CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o: CMakeFiles/lambda-invoke.dir/flags.make
CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o: ../src/ExcameraRetryStrategy.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kvasukib/LambdaPerf/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o -c /home/kvasukib/LambdaPerf/src/ExcameraRetryStrategy.cpp

CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kvasukib/LambdaPerf/src/ExcameraRetryStrategy.cpp > CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.i

CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kvasukib/LambdaPerf/src/ExcameraRetryStrategy.cpp -o CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.s

CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.requires:
.PHONY : CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.requires

CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.provides: CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.requires
	$(MAKE) -f CMakeFiles/lambda-invoke.dir/build.make CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.provides.build
.PHONY : CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.provides

CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.provides.build: CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o

CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o: CMakeFiles/lambda-invoke.dir/flags.make
CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o: ../src/LambdaInvocationRecord.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kvasukib/LambdaPerf/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o -c /home/kvasukib/LambdaPerf/src/LambdaInvocationRecord.cpp

CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kvasukib/LambdaPerf/src/LambdaInvocationRecord.cpp > CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.i

CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kvasukib/LambdaPerf/src/LambdaInvocationRecord.cpp -o CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.s

CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.requires:
.PHONY : CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.requires

CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.provides: CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.requires
	$(MAKE) -f CMakeFiles/lambda-invoke.dir/build.make CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.provides.build
.PHONY : CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.provides

CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.provides.build: CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o

CMakeFiles/lambda-invoke.dir/src/lib.cpp.o: CMakeFiles/lambda-invoke.dir/flags.make
CMakeFiles/lambda-invoke.dir/src/lib.cpp.o: ../src/lib.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kvasukib/LambdaPerf/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lambda-invoke.dir/src/lib.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lambda-invoke.dir/src/lib.cpp.o -c /home/kvasukib/LambdaPerf/src/lib.cpp

CMakeFiles/lambda-invoke.dir/src/lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lambda-invoke.dir/src/lib.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kvasukib/LambdaPerf/src/lib.cpp > CMakeFiles/lambda-invoke.dir/src/lib.cpp.i

CMakeFiles/lambda-invoke.dir/src/lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lambda-invoke.dir/src/lib.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kvasukib/LambdaPerf/src/lib.cpp -o CMakeFiles/lambda-invoke.dir/src/lib.cpp.s

CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.requires:
.PHONY : CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.requires

CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.provides: CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.requires
	$(MAKE) -f CMakeFiles/lambda-invoke.dir/build.make CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.provides.build
.PHONY : CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.provides

CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.provides.build: CMakeFiles/lambda-invoke.dir/src/lib.cpp.o

CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o: CMakeFiles/lambda-invoke.dir/flags.make
CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o: ../src/RequestParams.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kvasukib/LambdaPerf/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o -c /home/kvasukib/LambdaPerf/src/RequestParams.cpp

CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kvasukib/LambdaPerf/src/RequestParams.cpp > CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.i

CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kvasukib/LambdaPerf/src/RequestParams.cpp -o CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.s

CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.requires:
.PHONY : CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.requires

CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.provides: CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.requires
	$(MAKE) -f CMakeFiles/lambda-invoke.dir/build.make CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.provides.build
.PHONY : CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.provides

CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.provides.build: CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o

# Object files for target lambda-invoke
lambda__invoke_OBJECTS = \
"CMakeFiles/lambda-invoke.dir/src/main.cpp.o" \
"CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o" \
"CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o" \
"CMakeFiles/lambda-invoke.dir/src/lib.cpp.o" \
"CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o"

# External object files for target lambda-invoke
lambda__invoke_EXTERNAL_OBJECTS =

lambda-invoke: CMakeFiles/lambda-invoke.dir/src/main.cpp.o
lambda-invoke: CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o
lambda-invoke: CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o
lambda-invoke: CMakeFiles/lambda-invoke.dir/src/lib.cpp.o
lambda-invoke: CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o
lambda-invoke: CMakeFiles/lambda-invoke.dir/build.make
lambda-invoke: /home/kvasukib/build-aws-sdk-cpp/aws-cpp-sdk-s3/libaws-cpp-sdk-s3.so
lambda-invoke: /home/kvasukib/build-aws-sdk-cpp/aws-cpp-sdk-lambda/libaws-cpp-sdk-lambda.so
lambda-invoke: /home/kvasukib/build-aws-sdk-cpp/aws-cpp-sdk-core/libaws-cpp-sdk-core.so
lambda-invoke: CMakeFiles/lambda-invoke.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lambda-invoke"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lambda-invoke.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lambda-invoke.dir/build: lambda-invoke
.PHONY : CMakeFiles/lambda-invoke.dir/build

CMakeFiles/lambda-invoke.dir/requires: CMakeFiles/lambda-invoke.dir/src/main.cpp.o.requires
CMakeFiles/lambda-invoke.dir/requires: CMakeFiles/lambda-invoke.dir/src/ExcameraRetryStrategy.cpp.o.requires
CMakeFiles/lambda-invoke.dir/requires: CMakeFiles/lambda-invoke.dir/src/LambdaInvocationRecord.cpp.o.requires
CMakeFiles/lambda-invoke.dir/requires: CMakeFiles/lambda-invoke.dir/src/lib.cpp.o.requires
CMakeFiles/lambda-invoke.dir/requires: CMakeFiles/lambda-invoke.dir/src/RequestParams.cpp.o.requires
.PHONY : CMakeFiles/lambda-invoke.dir/requires

CMakeFiles/lambda-invoke.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lambda-invoke.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lambda-invoke.dir/clean

CMakeFiles/lambda-invoke.dir/depend:
	cd /home/kvasukib/LambdaPerf/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kvasukib/LambdaPerf /home/kvasukib/LambdaPerf /home/kvasukib/LambdaPerf/build /home/kvasukib/LambdaPerf/build /home/kvasukib/LambdaPerf/build/CMakeFiles/lambda-invoke.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lambda-invoke.dir/depend

