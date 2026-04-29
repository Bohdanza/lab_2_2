cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 23)

project(lab_2_2 VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND WIN32)
    # 1. Tell Clang to generate CodeView debug information
    add_compile_options(-gcodeview)

    # 2. Tell the Linker to create a Windows PDB file
    # Note: We use -Xlinker to pass the /DEBUG flag directly to the underlying linker
    add_link_options("-Xlinker" "/DEBUG")
endif()

add_executable(lab_2_2 ${SOURCE_FILES})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND WIN32)
    target_compile_options(lab_2_2 PRIVATE 
            $<$<CONFIG:Debug>:-gcodeview>
            $<$<CONFIG:Debug>:-fstandalone-debug>
        )
endif()