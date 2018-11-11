cmake_minimum_required(VERSION 3.5)

project (Tetris)
set(ENGINE_NAME Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_C_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
	endif()
endif()


if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	set(CONFIGURATION "x64")
else() 
	set(CONFIGURATION "x86")
endif() 

set(SDL2_PATH "C:/Program Files/SDL2")
set(ENGINE_DIR "${PROJECT_SOURCE_DIR}/engine")
set(APP_DIR "${PROJECT_SOURCE_DIR}/example")

add_subdirectory(engine)
add_subdirectory(example)