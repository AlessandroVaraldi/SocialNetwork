# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.1.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.1.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/PROGETTO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PROGETTO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PROGETTO.dir/flags.make

CMakeFiles/PROGETTO.dir/main.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PROGETTO.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\main.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\main.cpp"

CMakeFiles/PROGETTO.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\main.cpp" > CMakeFiles\PROGETTO.dir\main.cpp.i

CMakeFiles/PROGETTO.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\main.cpp" -o CMakeFiles\PROGETTO.dir\main.cpp.s

CMakeFiles/PROGETTO.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/main.cpp.obj.requires

CMakeFiles/PROGETTO.dir/main.cpp.obj.provides: CMakeFiles/PROGETTO.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/main.cpp.obj.provides

CMakeFiles/PROGETTO.dir/main.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/main.cpp.obj


CMakeFiles/PROGETTO.dir/User.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/User.cpp.obj: ../User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PROGETTO.dir/User.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\User.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\User.cpp"

CMakeFiles/PROGETTO.dir/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/User.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\User.cpp" > CMakeFiles\PROGETTO.dir\User.cpp.i

CMakeFiles/PROGETTO.dir/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/User.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\User.cpp" -o CMakeFiles\PROGETTO.dir\User.cpp.s

CMakeFiles/PROGETTO.dir/User.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/User.cpp.obj.requires

CMakeFiles/PROGETTO.dir/User.cpp.obj.provides: CMakeFiles/PROGETTO.dir/User.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/User.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/User.cpp.obj.provides

CMakeFiles/PROGETTO.dir/User.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/User.cpp.obj


CMakeFiles/PROGETTO.dir/Logger.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/Logger.cpp.obj: ../Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PROGETTO.dir/Logger.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\Logger.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Logger.cpp"

CMakeFiles/PROGETTO.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/Logger.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Logger.cpp" > CMakeFiles\PROGETTO.dir\Logger.cpp.i

CMakeFiles/PROGETTO.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/Logger.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Logger.cpp" -o CMakeFiles\PROGETTO.dir\Logger.cpp.s

CMakeFiles/PROGETTO.dir/Logger.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/Logger.cpp.obj.requires

CMakeFiles/PROGETTO.dir/Logger.cpp.obj.provides: CMakeFiles/PROGETTO.dir/Logger.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/Logger.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/Logger.cpp.obj.provides

CMakeFiles/PROGETTO.dir/Logger.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/Logger.cpp.obj


CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj: ../Simple_User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\Simple_User.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Simple_User.cpp"

CMakeFiles/PROGETTO.dir/Simple_User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/Simple_User.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Simple_User.cpp" > CMakeFiles\PROGETTO.dir\Simple_User.cpp.i

CMakeFiles/PROGETTO.dir/Simple_User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/Simple_User.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Simple_User.cpp" -o CMakeFiles\PROGETTO.dir\Simple_User.cpp.s

CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.requires

CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.provides: CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.provides

CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj


CMakeFiles/PROGETTO.dir/Company_User.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/Company_User.cpp.obj: ../Company_User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PROGETTO.dir/Company_User.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\Company_User.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Company_User.cpp"

CMakeFiles/PROGETTO.dir/Company_User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/Company_User.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Company_User.cpp" > CMakeFiles\PROGETTO.dir\Company_User.cpp.i

CMakeFiles/PROGETTO.dir/Company_User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/Company_User.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Company_User.cpp" -o CMakeFiles\PROGETTO.dir\Company_User.cpp.s

CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.requires

CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.provides: CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.provides

CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/Company_User.cpp.obj


CMakeFiles/PROGETTO.dir/Group_User.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/Group_User.cpp.obj: ../Group_User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PROGETTO.dir/Group_User.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\Group_User.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Group_User.cpp"

CMakeFiles/PROGETTO.dir/Group_User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/Group_User.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Group_User.cpp" > CMakeFiles\PROGETTO.dir\Group_User.cpp.i

CMakeFiles/PROGETTO.dir/Group_User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/Group_User.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Group_User.cpp" -o CMakeFiles\PROGETTO.dir\Group_User.cpp.s

CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.requires

CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.provides: CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.provides

CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/Group_User.cpp.obj


CMakeFiles/PROGETTO.dir/News.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/News.cpp.obj: ../News.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/PROGETTO.dir/News.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\News.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\News.cpp"

CMakeFiles/PROGETTO.dir/News.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/News.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\News.cpp" > CMakeFiles\PROGETTO.dir\News.cpp.i

CMakeFiles/PROGETTO.dir/News.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/News.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\News.cpp" -o CMakeFiles\PROGETTO.dir\News.cpp.s

CMakeFiles/PROGETTO.dir/News.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/News.cpp.obj.requires

CMakeFiles/PROGETTO.dir/News.cpp.obj.provides: CMakeFiles/PROGETTO.dir/News.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/News.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/News.cpp.obj.provides

CMakeFiles/PROGETTO.dir/News.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/News.cpp.obj


CMakeFiles/PROGETTO.dir/Date.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/Date.cpp.obj: ../Date.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/PROGETTO.dir/Date.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\Date.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Date.cpp"

CMakeFiles/PROGETTO.dir/Date.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/Date.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Date.cpp" > CMakeFiles\PROGETTO.dir\Date.cpp.i

CMakeFiles/PROGETTO.dir/Date.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/Date.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Date.cpp" -o CMakeFiles\PROGETTO.dir\Date.cpp.s

CMakeFiles/PROGETTO.dir/Date.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/Date.cpp.obj.requires

CMakeFiles/PROGETTO.dir/Date.cpp.obj.provides: CMakeFiles/PROGETTO.dir/Date.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/Date.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/Date.cpp.obj.provides

CMakeFiles/PROGETTO.dir/Date.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/Date.cpp.obj


CMakeFiles/PROGETTO.dir/Address.cpp.obj: CMakeFiles/PROGETTO.dir/flags.make
CMakeFiles/PROGETTO.dir/Address.cpp.obj: ../Address.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/PROGETTO.dir/Address.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PROGETTO.dir\Address.cpp.obj -c "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Address.cpp"

CMakeFiles/PROGETTO.dir/Address.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PROGETTO.dir/Address.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Address.cpp" > CMakeFiles\PROGETTO.dir\Address.cpp.i

CMakeFiles/PROGETTO.dir/Address.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PROGETTO.dir/Address.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\Address.cpp" -o CMakeFiles\PROGETTO.dir\Address.cpp.s

CMakeFiles/PROGETTO.dir/Address.cpp.obj.requires:

.PHONY : CMakeFiles/PROGETTO.dir/Address.cpp.obj.requires

CMakeFiles/PROGETTO.dir/Address.cpp.obj.provides: CMakeFiles/PROGETTO.dir/Address.cpp.obj.requires
	$(MAKE) -f CMakeFiles\PROGETTO.dir\build.make CMakeFiles/PROGETTO.dir/Address.cpp.obj.provides.build
.PHONY : CMakeFiles/PROGETTO.dir/Address.cpp.obj.provides

CMakeFiles/PROGETTO.dir/Address.cpp.obj.provides.build: CMakeFiles/PROGETTO.dir/Address.cpp.obj


# Object files for target PROGETTO
PROGETTO_OBJECTS = \
"CMakeFiles/PROGETTO.dir/main.cpp.obj" \
"CMakeFiles/PROGETTO.dir/User.cpp.obj" \
"CMakeFiles/PROGETTO.dir/Logger.cpp.obj" \
"CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj" \
"CMakeFiles/PROGETTO.dir/Company_User.cpp.obj" \
"CMakeFiles/PROGETTO.dir/Group_User.cpp.obj" \
"CMakeFiles/PROGETTO.dir/News.cpp.obj" \
"CMakeFiles/PROGETTO.dir/Date.cpp.obj" \
"CMakeFiles/PROGETTO.dir/Address.cpp.obj"

# External object files for target PROGETTO
PROGETTO_EXTERNAL_OBJECTS =

PROGETTO.exe: CMakeFiles/PROGETTO.dir/main.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/User.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/Logger.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/Company_User.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/Group_User.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/News.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/Date.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/Address.cpp.obj
PROGETTO.exe: CMakeFiles/PROGETTO.dir/build.make
PROGETTO.exe: CMakeFiles/PROGETTO.dir/linklibs.rsp
PROGETTO.exe: CMakeFiles/PROGETTO.dir/objects1.rsp
PROGETTO.exe: CMakeFiles/PROGETTO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable PROGETTO.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PROGETTO.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PROGETTO.dir/build: PROGETTO.exe

.PHONY : CMakeFiles/PROGETTO.dir/build

CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/main.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/User.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/Logger.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/Simple_User.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/Company_User.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/Group_User.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/News.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/Date.cpp.obj.requires
CMakeFiles/PROGETTO.dir/requires: CMakeFiles/PROGETTO.dir/Address.cpp.obj.requires

.PHONY : CMakeFiles/PROGETTO.dir/requires

CMakeFiles/PROGETTO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PROGETTO.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PROGETTO.dir/clean

CMakeFiles/PROGETTO.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO" "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO" "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug" "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug" "C:\Users\Alessio\Desktop\Nuova cartella\Progetto-di-Algoritmi-master\PROGETTO\cmake-build-debug\CMakeFiles\PROGETTO.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/PROGETTO.dir/depend
