cmake_minimum_required(VERSION 3.22)

project(hive_test VERSION 0.1)
set(TARGET_NAME pong)

set(CMAKE_CXX_STANDARD 20)

if(APPLE)
    set(SFML_ROOT libs/SFML/macos)
    SET(CMAKE_OSX_ARCHITECTURES "x86_64")
else()
    set(SFML_ROOT libs/SFML/win)
endif()

set(SFML_INCLUDE_PATH "${SFML_ROOT}/include")
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file(GLOB_RECURSE SOURCES
 src/*.mm
 src/*.m
 src/*.cpp
 src/*.c
 src/*.cxx
 src/*.h
)

file(GLOB_RECURSE SFML_INCLUDES
 ${SFML_INCLUDE_PATH}/*.mm
 ${SFML_INCLUDE_PATH}/*.m
 ${SFML_INCLUDE_PATH}/*.cpp
 ${SFML_INCLUDE_PATH}/*.c
 ${SFML_INCLUDE_PATH}/*.cxx
 ${SFML_INCLUDE_PATH}/*.h
 ${SFML_INCLUDE_PATH}/*.hpp
 ${SFML_INCLUDE_PATH}/*.inc
)

source_group(TREE src PREFIX "src" FILES ${SOURCES})
source_group(TREE ${SFML_INCLUDE_PATH} PREFIX "sfml" FILES ${SFML_INCLUDES})
add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SOURCES} ${SFML_INCLUDES})

message(${SFML_INCLUDE_PATH})
target_include_directories(${TARGET_NAME} PRIVATE ${SFML_INCLUDE_PATH})



if(APPLE)
    set(SFML_FRAMEWORKS ${SFML_ROOT}/Frameworks)
    set(SFML_FRAMEWORKS_EXT ${SFML_ROOT}/extlibs/Frameworks)

    # macos configuration
    find_library(SFML_AUDIO sfml-audio PATHS ${SFML_FRAMEWORKS} REQUIRED)
    find_library(SFML_GRAPHICS sfml-graphics PATHS ${SFML_FRAMEWORKS} REQUIRED)
    find_library(SFML_NEWORK sfml-network PATHS ${SFML_FRAMEWORKS} REQUIRED)
    find_library(SFML_SYSTEM sfml-system PATHS ${SFML_FRAMEWORKS} REQUIRED)
    find_library(SFML_WINDOW sfml-window PATHS ${SFML_FRAMEWORKS} REQUIRED)
    find_library(SFML SFML PATHS ${SFML_FRAMEWORKS} REQUIRED)

    find_library(SFML_EXT_FLAC FLAC PATHS ${SFML_FRAMEWORKS_EXT} REQUIRED NO_DEFAULT_PATH)
    find_library(SFML_EXT_FREETYPE freetype PATHS ${SFML_FRAMEWORKS_EXT} REQUIRED)
    find_library(SFML_EXT_OGG ogg PATHS ${SFML_FRAMEWORKS_EXT} REQUIRED)
    find_library(SFML_EXT_OPENAL OpenAL PATHS ${SFML_FRAMEWORKS_EXT} REQUIRED)
    find_library(SFML_EXT_VORBIS vorbis PATHS ${SFML_FRAMEWORKS_EXT} REQUIRED)
    find_library(SFML_EXT_VORBISENC vorbisenc PATHS ${SFML_FRAMEWORKS_EXT} REQUIRED)
    find_library(SFML_EXT_VORBISFILE vorbisfile PATHS ${SFML_FRAMEWORKS_EXT} REQUIRED)
    find_library(FOUNDATION foundation REQUIRED)

    #message(${SFML_AUDIO})
    set(ALL_FRAMEWORKS 
            ${SFML_AUDIO}
            ${SFML_GRAPHICS}
            ${SFML_NEWORK}
            ${SFML_SYSTEM}
            ${SFML_WINDOW}
            ${SFML}
            ${SFML_EXT_FLAC}
            ${SFML_EXT_FREETYPE}
            ${SFML_EXT_OGG}
            ${SFML_EXT_VORBIS}
            ${SFML_EXT_VORBISENC}
            ${SFML_EXT_VORBISFILE}
            ${SFML_EXT_OPENAL}
            ${FOUNDATION}
            )

    target_link_libraries(${TARGET_NAME} ${ALL_FRAMEWORKS})

    file(GLOB RESOURCE_FILES "assets")
    set_source_files_properties("${RESOURCE_FILES}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    target_sources(${TARGET_NAME} PRIVATE ${RESOURCE_FILES})

    set_target_properties(${TARGET_NAME} PROPERTIES
        RESOURCE "${RESOURCE_FILES}"
    )
else()
    set(SFML_FRAMEWORKS ${SFML_ROOT}/lib)

    target_link_libraries(${TARGET_NAME} 
        freetype.lib
        flac.lib
        ogg.lib
        OpenAL32.lib
        vorbis.lib
        vorbisenc.lib
        vorbisfile.lib
        )

    target_link_libraries(${TARGET_NAME} 
        debug sfml-audio-d.lib
        debug sfml-graphics-d.lib 
        debug sfml-network-d.lib 
        debug sfml-system-d.lib
        debug sfml-window-d.lib
        )

    target_link_libraries(${TARGET_NAME} 
        optimized sfml-audio.lib
        optimized fml-graphics.lib 
        optimized fml-network.lib 
        optimized fml-system.lib
        optimized fml-window.lib
        )

    target_link_directories(${TARGET_NAME} PRIVATE ${SFML_ROOT}/lib)

    set(DLL_PATH libs/SFML/win/bin)
    cmake_path(ABSOLUTE_PATH DLL_PATH OUTPUT_VARIABLE DLL_PATH)
    set(WORKING_PATH assets)
    cmake_path(ABSOLUTE_PATH WORKING_PATH OUTPUT_VARIABLE WORKING_PATH)
    set_target_properties(${TARGET_NAME} PROPERTIES
        VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${DLL_PATH}"
        VS_DEBUGGER_WORKING_DIRECTORY ${WORKING_PATH}
    )

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

endif()
