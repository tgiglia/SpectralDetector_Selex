#
# Copyright 2014-2015 Ettus Research LLC
# Copyright 2018 Ettus Research, a National Instruments Company
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.5.1)
project(RX_ASCII_ART_DFT CXX)

### Configure Compiler ########################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENTIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "-lthr ${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()

### Set up build environment ##################################################
# Choose a static or shared-library build (shared is default, and static will
# probably need some special care!)
# Set this to ON in order to link a static build of UHD:
option(UHD_USE_STATIC_LIBS OFF)


# To add UHD as a dependency to this project, add a line such as this:
find_package(UHD 4.1.0 REQUIRED)
# The version in  ^^^^^  here is a minimum version.
# To specify an exact version:
#find_package(UHD 4.0.0 EXACT REQUIRED)

# This example also requires Boost.
# Set components here, then include UHDBoost to do the actual finding
set(UHD_BOOST_REQUIRED_COMPONENTS
    chrono
    date_time
    filesystem
    program_options
    system
    serialization
    thread
    unit_test_framework
)
set(BOOST_MIN_VERSION 1.65)
include(UHDBoost)

set(CURSES_NEED_NCURSES 1)
find_package(Curses)


# need these include and link directories for the build
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${UHD_INCLUDE_DIRS}
    ${CURSES_INCLUDE_DIR}
)
link_directories(${CURSES_LIBRARIES} ${Boost_LIBRARY_DIRS} )

### Make the executable #######################################################
add_executable(SpectralDetector rx_ascii_art_dft.cpp AnalyzeRelativeGain.cpp RESTUtils.cpp NotifyInfo.cpp Logger.cpp EOCXmlMaker.cpp ConfigData.cpp ThreadSafeStack.cpp DetectionConsumer.cpp)

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "RelWithDebInfo") 
message(STATUS "******************************************************************************")
message(STATUS "* NOTE: When building your own app, you probably need all kinds of different  ")
message(STATUS "* compiler flags. This is just an example, so it's unlikely these settings    ")
message(STATUS "* exactly match what you require. Make sure to double-check compiler and     ")
message(STATUS "* linker flags to make sure your specific requirements are included.          ")
message(STATUS "******************************************************************************")

# Shared library case: All we need to do is link against the library, and
# anything else we need (in this case, some Boost libraries):
if(NOT UHD_USE_STATIC_LIBS)
    message(STATUS "Linking against shared UHD library.")
    target_link_libraries(SpectralDetector ${UHD_LIBRARIES} ${Boost_LIBRARIES} ${CURSES_LIBRARIES} )
# Shared library case: All we need to do is link against the library, and
# anything else we need (in this case, some Boost libraries):
else(NOT UHD_USE_STATIC_LIBS)
    message(STATUS "Linking against static UHD library.")
    target_link_libraries(SpectralDetector
        # We could use ${UHD_LIBRARIES}, but linking requires some extra flags,
        # so we use this convenience variable provided to us
        ${UHD_STATIC_LIB_LINK_FLAG}
        # Also, when linking statically, we need to pull in all the deps for
        # UHD as well, because the dependencies don't get resolved automatically
        ${UHD_STATIC_LIB_DEPS}
    )
endif(NOT UHD_USE_STATIC_LIBS)

### Once it's built... ########################################################
# Here, you would have commands to install your program.
# We will skip these in this example.
