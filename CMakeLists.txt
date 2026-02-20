cmake_minimum_required(VERSION 3.16)

project(Battleship VERSION 1.0 LANGUAGES CXX)

# ---------------------------
# C++ Standard & Compiler Warnings
# ---------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
	add_compile_options(/W4 /permissive-)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---------------------------
# Build type defaults
# ---------------------------
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# ---------------------------
# Core library sources
# ---------------------------
file(GLOB_RECURSE LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(battleship_lib STATIC ${LIB_SOURCES})
target_include_directories(battleship_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# ---------------------------
# Main executable
# ---------------------------
add_executable(BattNavale src/main.cpp)
target_link_libraries(BattNavale PRIVATE battleship_lib)

add_custom_target(run
	COMMAND BattNavale
	DEPENDS BattNavale
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Running BattNavale..."
)

install(TARGETS BattNavale RUNTIME DESTINATION bin)

# ---------------------------
# Testing
# ---------------------------
include(CTest)

if (BUILD_TESTING)
	message(STATUS "Building tests enabled")

	file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

	include(FetchContent)
	FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG v3.5.0
	)
	FetchContent_MakeAvailable(Catch2)

	add_executable(tests ${TEST_SOURCES})
	target_link_libraries(tests PRIVATE battleship_lib Catch2::Catch2WithMain)
	add_test(NAME all_tests COMMAND tests)
endif()

