# Project : OOM-Engine (Out-Of-Memory Engine)
# GitHub  : https://github.com/Aredhele/OOM-Engine
# Author  : Vincent STEHLY--CALISTO (Ardhele)
# See     : https://vincencalisto.com

PROJECT               (OOM-Engine)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# Getting sources and headers
FILE(GLOB_RECURSE ENGINE_SOURCES *.cpp)
FILE(GLOB_RECURSE ENGINE_HEADERS
        ${CMAKE_SOURCE_DIR}/Header/*.hpp
        ${CMAKE_SOURCE_DIR}/Header/*.h
        ${CMAKE_SOURCE_DIR}/Header/*.inl)
ADD_DEFINITIONS      (-DGLEW_STATIC -DVC_EXTRALEAN -D_AFX_NO_MFC_CONTROLS_IN_DIALOGS -DNOMINMAX)
ADD_EXECUTABLE       (OOM-Engine ${ENGINE_SOURCES} ${ENGINE_HEADERS})
ADD_CUSTOM_TARGET    (Copy_resources)
ADD_DEPENDENCIES     (OOM-Engine Copy_resources)

IF(NOT ${CMAKE_BUILD_TYPE} MATCHES Debug)
	set_property(TARGET OOM-Engine APPEND_STRING PROPERTY COMPILE_FLAGS " /GL /Oy /O1 /Os")
	set_property(TARGET OOM-Engine APPEND_STRING PROPERTY LINK_FLAGS    " /DYNAMICBASE:NO /NODEFAULTLIB /OPT:REF /OPT:ICF /LTCG")
ENDIF()

IF(${CMAKE_BUILD_TYPE} MATCHES Debug)
	TARGET_LINK_LIBRARIES(OOM-Engine glfw3d glew32d opengl32 qu3ed Windowscodecs dxguid dsound vorbisd oggd)
ELSE()
	TARGET_LINK_LIBRARIES(OOM-Engine vcruntime ucrt msvcrt msvcprt glfw3 glew32 opengl32 qu3e Windowscodecs dxguid dsound vorbis ogg)
ENDIF()

ADD_CUSTOM_COMMAND(TARGET Copy_resources PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Engine/Resources ${CMAKE_SOURCE_DIR}/Bin/Resources
        COMMENT "[INFO] Copying resource files ...")
