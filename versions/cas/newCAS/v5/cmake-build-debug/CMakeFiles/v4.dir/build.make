# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\CLion 2020.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\hz\cpp_homework\CAS_test\v5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/v4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/v4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/v4.dir/flags.make

CMakeFiles/v4.dir/main.cpp.obj: CMakeFiles/v4.dir/flags.make
CMakeFiles/v4.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/v4.dir/main.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\v4.dir\main.cpp.obj -c E:\hz\cpp_homework\CAS_test\v5\main.cpp

CMakeFiles/v4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/v4.dir/main.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\hz\cpp_homework\CAS_test\v5\main.cpp > CMakeFiles\v4.dir\main.cpp.i

CMakeFiles/v4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/v4.dir/main.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\hz\cpp_homework\CAS_test\v5\main.cpp -o CMakeFiles\v4.dir\main.cpp.s

CMakeFiles/v4.dir/biginteger.cpp.obj: CMakeFiles/v4.dir/flags.make
CMakeFiles/v4.dir/biginteger.cpp.obj: ../biginteger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/v4.dir/biginteger.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\v4.dir\biginteger.cpp.obj -c E:\hz\cpp_homework\CAS_test\v5\biginteger.cpp

CMakeFiles/v4.dir/biginteger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/v4.dir/biginteger.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\hz\cpp_homework\CAS_test\v5\biginteger.cpp > CMakeFiles\v4.dir\biginteger.cpp.i

CMakeFiles/v4.dir/biginteger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/v4.dir/biginteger.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\hz\cpp_homework\CAS_test\v5\biginteger.cpp -o CMakeFiles\v4.dir\biginteger.cpp.s

CMakeFiles/v4.dir/rational.cpp.obj: CMakeFiles/v4.dir/flags.make
CMakeFiles/v4.dir/rational.cpp.obj: ../rational.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/v4.dir/rational.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\v4.dir\rational.cpp.obj -c E:\hz\cpp_homework\CAS_test\v5\rational.cpp

CMakeFiles/v4.dir/rational.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/v4.dir/rational.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\hz\cpp_homework\CAS_test\v5\rational.cpp > CMakeFiles\v4.dir\rational.cpp.i

CMakeFiles/v4.dir/rational.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/v4.dir/rational.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\hz\cpp_homework\CAS_test\v5\rational.cpp -o CMakeFiles\v4.dir\rational.cpp.s

CMakeFiles/v4.dir/poly.cpp.obj: CMakeFiles/v4.dir/flags.make
CMakeFiles/v4.dir/poly.cpp.obj: ../poly.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/v4.dir/poly.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\v4.dir\poly.cpp.obj -c E:\hz\cpp_homework\CAS_test\v5\poly.cpp

CMakeFiles/v4.dir/poly.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/v4.dir/poly.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\hz\cpp_homework\CAS_test\v5\poly.cpp > CMakeFiles\v4.dir\poly.cpp.i

CMakeFiles/v4.dir/poly.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/v4.dir/poly.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\hz\cpp_homework\CAS_test\v5\poly.cpp -o CMakeFiles\v4.dir\poly.cpp.s

CMakeFiles/v4.dir/trig.cpp.obj: CMakeFiles/v4.dir/flags.make
CMakeFiles/v4.dir/trig.cpp.obj: ../trig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/v4.dir/trig.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\v4.dir\trig.cpp.obj -c E:\hz\cpp_homework\CAS_test\v5\trig.cpp

CMakeFiles/v4.dir/trig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/v4.dir/trig.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\hz\cpp_homework\CAS_test\v5\trig.cpp > CMakeFiles\v4.dir\trig.cpp.i

CMakeFiles/v4.dir/trig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/v4.dir/trig.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\hz\cpp_homework\CAS_test\v5\trig.cpp -o CMakeFiles\v4.dir\trig.cpp.s

CMakeFiles/v4.dir/factor.cpp.obj: CMakeFiles/v4.dir/flags.make
CMakeFiles/v4.dir/factor.cpp.obj: ../factor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/v4.dir/factor.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\v4.dir\factor.cpp.obj -c E:\hz\cpp_homework\CAS_test\v5\factor.cpp

CMakeFiles/v4.dir/factor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/v4.dir/factor.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\hz\cpp_homework\CAS_test\v5\factor.cpp > CMakeFiles\v4.dir\factor.cpp.i

CMakeFiles/v4.dir/factor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/v4.dir/factor.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\hz\cpp_homework\CAS_test\v5\factor.cpp -o CMakeFiles\v4.dir\factor.cpp.s

CMakeFiles/v4.dir/radicalextension.cpp.obj: CMakeFiles/v4.dir/flags.make
CMakeFiles/v4.dir/radicalextension.cpp.obj: ../radicalextension.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/v4.dir/radicalextension.cpp.obj"
	"D:\Program Files\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\v4.dir\radicalextension.cpp.obj -c E:\hz\cpp_homework\CAS_test\v5\radicalextension.cpp

CMakeFiles/v4.dir/radicalextension.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/v4.dir/radicalextension.cpp.i"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\hz\cpp_homework\CAS_test\v5\radicalextension.cpp > CMakeFiles\v4.dir\radicalextension.cpp.i

CMakeFiles/v4.dir/radicalextension.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/v4.dir/radicalextension.cpp.s"
	"D:\Program Files\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\hz\cpp_homework\CAS_test\v5\radicalextension.cpp -o CMakeFiles\v4.dir\radicalextension.cpp.s

# Object files for target v4
v4_OBJECTS = \
"CMakeFiles/v4.dir/main.cpp.obj" \
"CMakeFiles/v4.dir/biginteger.cpp.obj" \
"CMakeFiles/v4.dir/rational.cpp.obj" \
"CMakeFiles/v4.dir/poly.cpp.obj" \
"CMakeFiles/v4.dir/trig.cpp.obj" \
"CMakeFiles/v4.dir/factor.cpp.obj" \
"CMakeFiles/v4.dir/radicalextension.cpp.obj"

# External object files for target v4
v4_EXTERNAL_OBJECTS =

v4.exe: CMakeFiles/v4.dir/main.cpp.obj
v4.exe: CMakeFiles/v4.dir/biginteger.cpp.obj
v4.exe: CMakeFiles/v4.dir/rational.cpp.obj
v4.exe: CMakeFiles/v4.dir/poly.cpp.obj
v4.exe: CMakeFiles/v4.dir/trig.cpp.obj
v4.exe: CMakeFiles/v4.dir/factor.cpp.obj
v4.exe: CMakeFiles/v4.dir/radicalextension.cpp.obj
v4.exe: CMakeFiles/v4.dir/build.make
v4.exe: CMakeFiles/v4.dir/linklibs.rsp
v4.exe: CMakeFiles/v4.dir/objects1.rsp
v4.exe: CMakeFiles/v4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable v4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\v4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/v4.dir/build: v4.exe

.PHONY : CMakeFiles/v4.dir/build

CMakeFiles/v4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\v4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/v4.dir/clean

CMakeFiles/v4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\hz\cpp_homework\CAS_test\v5 E:\hz\cpp_homework\CAS_test\v5 E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug E:\hz\cpp_homework\CAS_test\v5\cmake-build-debug\CMakeFiles\v4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/v4.dir/depend

