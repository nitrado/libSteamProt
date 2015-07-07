set(targetname "steamquery")

project(${targetname} C CXX)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_FILES_DIRECTORY ${PROJECT_BINARY_DIR}/obj/${CMAKE_BUILD_TYPE})

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_FILES_DIRECTORY ${PROJECT_BINARY_DIR}/obj/${CMAKE_BUILD_TYPE})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32 /D_WINDOWS /D_CRT_SECURE_NO_WARNINGS /W3 /Zm500 /EHsc /GR /wd\"4996\"")

    # Compile on multiple processors
    add_definitions("/MP")
else(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64 -mtune=generic -Wno-unknown-pragmas -Wno-unused-variable")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -g3 -fno-inline")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O3 -g0")

	if(CMAKE_BUILD_TYPE MATCHES Debug)
		set(CMAKE_EXECUTABLE_SUFFIX "_d")
	endif()
endif(MSVC)

add_subdirectory(bzlib)
set(ALL_TARGETS ${ALL_TARGETS} bzlib)

add_subdirectory(src)
set(ALL_TARGETS ${ALL_TARGETS} libSteamProt)

add_subdirectory(test)
set(ALL_TARGETS ${ALL_TARGETS} queryserver)