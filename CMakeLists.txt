# Project : OOM-Engine (Out-Of-Memory Engine)
# GitHub  : https://github.com/Aredhele/OOM-Engine
# Author  : Vincent STEHLY--CALISTO (Ardhele)
# See     : https://vincencalisto.com

PROJECT               (OOM-Engine CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# C++ standard to draft C++20
# ADD_DEFINITIONS(-std=c++2a -fconcepts)
SET(CMAKE_CXX_STANDARD 17)

# Settings
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")

# Note :
# -O3     > AGRESSIVE optimization
# -s      > stripping ALL
# -static > Bundles gcc runtime into the .exe
# SET(CMAKE_C_FLAGS_RELEASE          "-O3 -s")
# SET(CMAKE_CXX_FLAGS_RELEASE        "-O3 -s")
# SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "-static -mwindows")

SET(CMAKE_CXX_FLAGS_RELEASE        "/GL /Oy /O1 /Os")

# Include / Lib directories
LINK_DIRECTORIES   (${CMAKE_SOURCE_DIR}/Lib)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Lib ${CMAKE_SOURCE_DIR}/Engine/Header)

# Compiling engine
ADD_SUBDIRECTORY(Engine/Source)
