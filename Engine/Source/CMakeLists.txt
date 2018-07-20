# Project : OOM-Engine (Out-Of-Memory Engine)
# GitHub  : https://github.com/Aredhele/OOM-Engine
# Author  : Vincent STEHLY--CALISTO (Ardhele)
# See     : https://vincencalisto.com

PROJECT               (OOM-Engine)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# Getting sources and headers
FILE(GLOB_RECURSE ENGINE_SOURCES *.cpp)
FILE(GLOB_RECURSE ENGINE_HEADERS *.hpp *.h *.inl)

ADD_EXECUTABLE       (OOM-Engine ${ENGINE_SOURCES} ${ENGINE_HEADERS})
TARGET_LINK_LIBRARIES(OOM-Engine glfw3 glew32)