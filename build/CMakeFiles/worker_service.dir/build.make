# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build

# Include any dependencies generated for this target.
include CMakeFiles/worker_service.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/worker_service.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/worker_service.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/worker_service.dir/flags.make

CMakeFiles/worker_service.dir/worker/worker_server.cpp.o: CMakeFiles/worker_service.dir/flags.make
CMakeFiles/worker_service.dir/worker/worker_server.cpp.o: /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/worker/worker_server.cpp
CMakeFiles/worker_service.dir/worker/worker_server.cpp.o: CMakeFiles/worker_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/worker_service.dir/worker/worker_server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/worker_service.dir/worker/worker_server.cpp.o -MF CMakeFiles/worker_service.dir/worker/worker_server.cpp.o.d -o CMakeFiles/worker_service.dir/worker/worker_server.cpp.o -c /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/worker/worker_server.cpp

CMakeFiles/worker_service.dir/worker/worker_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/worker_service.dir/worker/worker_server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/worker/worker_server.cpp > CMakeFiles/worker_service.dir/worker/worker_server.cpp.i

CMakeFiles/worker_service.dir/worker/worker_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/worker_service.dir/worker/worker_server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/worker/worker_server.cpp -o CMakeFiles/worker_service.dir/worker/worker_server.cpp.s

CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o: CMakeFiles/worker_service.dir/flags.make
CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o: /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.pb.cc
CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o: CMakeFiles/worker_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o -MF CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o.d -o CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o -c /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.pb.cc

CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.pb.cc > CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.i

CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.pb.cc -o CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.s

CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o: CMakeFiles/worker_service.dir/flags.make
CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o: /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.pb.cc
CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o: CMakeFiles/worker_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o -MF CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o.d -o CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o -c /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.pb.cc

CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.pb.cc > CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.i

CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.pb.cc -o CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.s

CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o: CMakeFiles/worker_service.dir/flags.make
CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o: /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.grpc.pb.cc
CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o: CMakeFiles/worker_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o -MF CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o.d -o CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o -c /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.grpc.pb.cc

CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.grpc.pb.cc > CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.i

CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/sql_service.grpc.pb.cc -o CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.s

CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o: CMakeFiles/worker_service.dir/flags.make
CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o: /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.grpc.pb.cc
CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o: CMakeFiles/worker_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o -MF CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o.d -o CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o -c /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.grpc.pb.cc

CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.grpc.pb.cc > CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.i

CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/proto/worker_service.grpc.pb.cc -o CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.s

# Object files for target worker_service
worker_service_OBJECTS = \
"CMakeFiles/worker_service.dir/worker/worker_server.cpp.o" \
"CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o" \
"CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o" \
"CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o" \
"CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o"

# External object files for target worker_service
worker_service_EXTERNAL_OBJECTS =

worker_service: CMakeFiles/worker_service.dir/worker/worker_server.cpp.o
worker_service: CMakeFiles/worker_service.dir/proto/sql_service.pb.cc.o
worker_service: CMakeFiles/worker_service.dir/proto/worker_service.pb.cc.o
worker_service: CMakeFiles/worker_service.dir/proto/sql_service.grpc.pb.cc.o
worker_service: CMakeFiles/worker_service.dir/proto/worker_service.grpc.pb.cc.o
worker_service: CMakeFiles/worker_service.dir/build.make
worker_service: CMakeFiles/worker_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable worker_service"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/worker_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/worker_service.dir/build: worker_service
.PHONY : CMakeFiles/worker_service.dir/build

CMakeFiles/worker_service.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/worker_service.dir/cmake_clean.cmake
.PHONY : CMakeFiles/worker_service.dir/clean

CMakeFiles/worker_service.dir/depend:
	cd /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build /Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/build/CMakeFiles/worker_service.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/worker_service.dir/depend

