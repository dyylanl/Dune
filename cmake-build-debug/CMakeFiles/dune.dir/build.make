# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /home/riclui/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/213.7172.20/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/riclui/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/213.7172.20/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/dune.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dune.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dune.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dune.dir/flags.make

CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o: CMakeFiles/dune.dir/flags.make
CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o: ../Client/src/SDL/Window.cpp
CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o: CMakeFiles/dune.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o -MF CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o.d -o CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o -c "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/Client/src/SDL/Window.cpp"

CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/Client/src/SDL/Window.cpp" > CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.i

CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/Client/src/SDL/Window.cpp" -o CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.s

CMakeFiles/dune.dir/Client/src/main.cpp.o: CMakeFiles/dune.dir/flags.make
CMakeFiles/dune.dir/Client/src/main.cpp.o: ../Client/src/main.cpp
CMakeFiles/dune.dir/Client/src/main.cpp.o: CMakeFiles/dune.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/dune.dir/Client/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dune.dir/Client/src/main.cpp.o -MF CMakeFiles/dune.dir/Client/src/main.cpp.o.d -o CMakeFiles/dune.dir/Client/src/main.cpp.o -c "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/Client/src/main.cpp"

CMakeFiles/dune.dir/Client/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dune.dir/Client/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/Client/src/main.cpp" > CMakeFiles/dune.dir/Client/src/main.cpp.i

CMakeFiles/dune.dir/Client/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dune.dir/Client/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/Client/src/main.cpp" -o CMakeFiles/dune.dir/Client/src/main.cpp.s

# Object files for target dune
dune_OBJECTS = \
"CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o" \
"CMakeFiles/dune.dir/Client/src/main.cpp.o"

# External object files for target dune
dune_EXTERNAL_OBJECTS =

dune: CMakeFiles/dune.dir/Client/src/SDL/Window.cpp.o
dune: CMakeFiles/dune.dir/Client/src/main.cpp.o
dune: CMakeFiles/dune.dir/build.make
dune: libdune-common.so
dune: /usr/lib/x86_64-linux-gnu/libSDL2main.a
dune: Client/libs/libSDL2pp/libSDL2pp.a
dune: /usr/lib/x86_64-linux-gnu/libSDL2.so
dune: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
dune: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
dune: CMakeFiles/dune.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable dune"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dune.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dune.dir/build: dune
.PHONY : CMakeFiles/dune.dir/build

CMakeFiles/dune.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dune.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dune.dir/clean

CMakeFiles/dune.dir/depend:
	cd "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune" "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune" "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug" "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug" "/home/riclui/Documentos/Fiuba/Taller de programacion I/Dune/cmake-build-debug/CMakeFiles/dune.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/dune.dir/depend

