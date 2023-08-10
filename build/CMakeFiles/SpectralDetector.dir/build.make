# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tgiglia/projects/SpectralDetector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tgiglia/projects/SpectralDetector/build

# Include any dependencies generated for this target.
include CMakeFiles/SpectralDetector.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SpectralDetector.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SpectralDetector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SpectralDetector.dir/flags.make

CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o: CMakeFiles/SpectralDetector.dir/flags.make
CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o: ../rx_ascii_art_dft.cpp
CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o: CMakeFiles/SpectralDetector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o -MF CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o.d -o CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o -c /home/tgiglia/projects/SpectralDetector/rx_ascii_art_dft.cpp

CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tgiglia/projects/SpectralDetector/rx_ascii_art_dft.cpp > CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.i

CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tgiglia/projects/SpectralDetector/rx_ascii_art_dft.cpp -o CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.s

CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o: CMakeFiles/SpectralDetector.dir/flags.make
CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o: ../AnalyzeRelativeGain.cpp
CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o: CMakeFiles/SpectralDetector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o -MF CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o.d -o CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o -c /home/tgiglia/projects/SpectralDetector/AnalyzeRelativeGain.cpp

CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tgiglia/projects/SpectralDetector/AnalyzeRelativeGain.cpp > CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.i

CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tgiglia/projects/SpectralDetector/AnalyzeRelativeGain.cpp -o CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.s

CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o: CMakeFiles/SpectralDetector.dir/flags.make
CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o: ../RESTUtils.cpp
CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o: CMakeFiles/SpectralDetector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o -MF CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o.d -o CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o -c /home/tgiglia/projects/SpectralDetector/RESTUtils.cpp

CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tgiglia/projects/SpectralDetector/RESTUtils.cpp > CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.i

CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tgiglia/projects/SpectralDetector/RESTUtils.cpp -o CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.s

CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o: CMakeFiles/SpectralDetector.dir/flags.make
CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o: ../NotifyInfo.cpp
CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o: CMakeFiles/SpectralDetector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o -MF CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o.d -o CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o -c /home/tgiglia/projects/SpectralDetector/NotifyInfo.cpp

CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tgiglia/projects/SpectralDetector/NotifyInfo.cpp > CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.i

CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tgiglia/projects/SpectralDetector/NotifyInfo.cpp -o CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.s

CMakeFiles/SpectralDetector.dir/Logger.cpp.o: CMakeFiles/SpectralDetector.dir/flags.make
CMakeFiles/SpectralDetector.dir/Logger.cpp.o: ../Logger.cpp
CMakeFiles/SpectralDetector.dir/Logger.cpp.o: CMakeFiles/SpectralDetector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SpectralDetector.dir/Logger.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpectralDetector.dir/Logger.cpp.o -MF CMakeFiles/SpectralDetector.dir/Logger.cpp.o.d -o CMakeFiles/SpectralDetector.dir/Logger.cpp.o -c /home/tgiglia/projects/SpectralDetector/Logger.cpp

CMakeFiles/SpectralDetector.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralDetector.dir/Logger.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tgiglia/projects/SpectralDetector/Logger.cpp > CMakeFiles/SpectralDetector.dir/Logger.cpp.i

CMakeFiles/SpectralDetector.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralDetector.dir/Logger.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tgiglia/projects/SpectralDetector/Logger.cpp -o CMakeFiles/SpectralDetector.dir/Logger.cpp.s

CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o: CMakeFiles/SpectralDetector.dir/flags.make
CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o: ../EOCXmlMaker.cpp
CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o: CMakeFiles/SpectralDetector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o -MF CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o.d -o CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o -c /home/tgiglia/projects/SpectralDetector/EOCXmlMaker.cpp

CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tgiglia/projects/SpectralDetector/EOCXmlMaker.cpp > CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.i

CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tgiglia/projects/SpectralDetector/EOCXmlMaker.cpp -o CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.s

CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o: CMakeFiles/SpectralDetector.dir/flags.make
CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o: ../ConfigData.cpp
CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o: CMakeFiles/SpectralDetector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o -MF CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o.d -o CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o -c /home/tgiglia/projects/SpectralDetector/ConfigData.cpp

CMakeFiles/SpectralDetector.dir/ConfigData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralDetector.dir/ConfigData.cpp.i"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tgiglia/projects/SpectralDetector/ConfigData.cpp > CMakeFiles/SpectralDetector.dir/ConfigData.cpp.i

CMakeFiles/SpectralDetector.dir/ConfigData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralDetector.dir/ConfigData.cpp.s"
	/usr/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tgiglia/projects/SpectralDetector/ConfigData.cpp -o CMakeFiles/SpectralDetector.dir/ConfigData.cpp.s

# Object files for target SpectralDetector
SpectralDetector_OBJECTS = \
"CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o" \
"CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o" \
"CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o" \
"CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o" \
"CMakeFiles/SpectralDetector.dir/Logger.cpp.o" \
"CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o" \
"CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o"

# External object files for target SpectralDetector
SpectralDetector_EXTERNAL_OBJECTS =

SpectralDetector: CMakeFiles/SpectralDetector.dir/rx_ascii_art_dft.cpp.o
SpectralDetector: CMakeFiles/SpectralDetector.dir/AnalyzeRelativeGain.cpp.o
SpectralDetector: CMakeFiles/SpectralDetector.dir/RESTUtils.cpp.o
SpectralDetector: CMakeFiles/SpectralDetector.dir/NotifyInfo.cpp.o
SpectralDetector: CMakeFiles/SpectralDetector.dir/Logger.cpp.o
SpectralDetector: CMakeFiles/SpectralDetector.dir/EOCXmlMaker.cpp.o
SpectralDetector: CMakeFiles/SpectralDetector.dir/ConfigData.cpp.o
SpectralDetector: CMakeFiles/SpectralDetector.dir/build.make
SpectralDetector: /usr/local/lib/libuhd.so
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_program_options.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_serialization.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_thread.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_unit_test_framework.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_system.so.1.74.0
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libncurses.so
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libform.so
SpectralDetector: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so.1.74.0
SpectralDetector: CMakeFiles/SpectralDetector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tgiglia/projects/SpectralDetector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable SpectralDetector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SpectralDetector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SpectralDetector.dir/build: SpectralDetector
.PHONY : CMakeFiles/SpectralDetector.dir/build

CMakeFiles/SpectralDetector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SpectralDetector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SpectralDetector.dir/clean

CMakeFiles/SpectralDetector.dir/depend:
	cd /home/tgiglia/projects/SpectralDetector/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tgiglia/projects/SpectralDetector /home/tgiglia/projects/SpectralDetector /home/tgiglia/projects/SpectralDetector/build /home/tgiglia/projects/SpectralDetector/build /home/tgiglia/projects/SpectralDetector/build/CMakeFiles/SpectralDetector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpectralDetector.dir/depend

