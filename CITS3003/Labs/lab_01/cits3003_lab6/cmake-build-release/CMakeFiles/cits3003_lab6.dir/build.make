# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/cits3003_lab6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cits3003_lab6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cits3003_lab6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cits3003_lab6.dir/flags.make

CMakeFiles/cits3003_lab6.dir/main.cpp.o: CMakeFiles/cits3003_lab6.dir/flags.make
CMakeFiles/cits3003_lab6.dir/main.cpp.o: /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/main.cpp
CMakeFiles/cits3003_lab6.dir/main.cpp.o: CMakeFiles/cits3003_lab6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cits3003_lab6.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cits3003_lab6.dir/main.cpp.o -MF CMakeFiles/cits3003_lab6.dir/main.cpp.o.d -o CMakeFiles/cits3003_lab6.dir/main.cpp.o -c /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/main.cpp

CMakeFiles/cits3003_lab6.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cits3003_lab6.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/main.cpp > CMakeFiles/cits3003_lab6.dir/main.cpp.i

CMakeFiles/cits3003_lab6.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cits3003_lab6.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/main.cpp -o CMakeFiles/cits3003_lab6.dir/main.cpp.s

CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o: CMakeFiles/cits3003_lab6.dir/flags.make
CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o: /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/ShaderHelper.cpp
CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o: CMakeFiles/cits3003_lab6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o -MF CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o.d -o CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o -c /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/ShaderHelper.cpp

CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/ShaderHelper.cpp > CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.i

CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/ShaderHelper.cpp -o CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.s

CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o: CMakeFiles/cits3003_lab6.dir/flags.make
CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o: /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiImpl.cpp
CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o: CMakeFiles/cits3003_lab6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o -MF CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o.d -o CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o -c /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiImpl.cpp

CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiImpl.cpp > CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.i

CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiImpl.cpp -o CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.s

CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o: CMakeFiles/cits3003_lab6.dir/flags.make
CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o: /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiManager.cpp
CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o: CMakeFiles/cits3003_lab6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o -MF CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o.d -o CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o -c /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiManager.cpp

CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiManager.cpp > CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.i

CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/helpers/imgui/ImGuiManager.cpp -o CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.s

# Object files for target cits3003_lab6
cits3003_lab6_OBJECTS = \
"CMakeFiles/cits3003_lab6.dir/main.cpp.o" \
"CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o" \
"CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o" \
"CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o"

# External object files for target cits3003_lab6
cits3003_lab6_EXTERNAL_OBJECTS =

cits3003_lab6: CMakeFiles/cits3003_lab6.dir/main.cpp.o
cits3003_lab6: CMakeFiles/cits3003_lab6.dir/helpers/ShaderHelper.cpp.o
cits3003_lab6: CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiImpl.cpp.o
cits3003_lab6: CMakeFiles/cits3003_lab6.dir/helpers/imgui/ImGuiManager.cpp.o
cits3003_lab6: CMakeFiles/cits3003_lab6.dir/build.make
cits3003_lab6: lib/glfw/src/libglfw3.a
cits3003_lab6: lib/glad/libglad.a
cits3003_lab6: lib/imgui/libimgui.a
cits3003_lab6: /usr/lib/x86_64-linux-gnu/librt.a
cits3003_lab6: /usr/lib/x86_64-linux-gnu/libm.so
cits3003_lab6: CMakeFiles/cits3003_lab6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable cits3003_lab6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cits3003_lab6.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/cits3003_lab6 /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6
	/usr/bin/cmake -E create_symlink /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/res /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/res
	/usr/bin/cmake -E create_symlink /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/config /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/config

# Rule to build all files generated by this target.
CMakeFiles/cits3003_lab6.dir/build: cits3003_lab6
.PHONY : CMakeFiles/cits3003_lab6.dir/build

CMakeFiles/cits3003_lab6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cits3003_lab6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cits3003_lab6.dir/clean

CMakeFiles/cits3003_lab6.dir/depend:
	cd /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6 /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6 /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release /home/sahil/Graphcis-and-animation/CITS3003/Labs/lab_01/cits3003_lab6/cmake-build-release/CMakeFiles/cits3003_lab6.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cits3003_lab6.dir/depend

