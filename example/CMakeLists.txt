set(APP_INCLUDE_DIRS
	include
	${ENGINE_DIR}/include
)

set(APP_HEADER_FILES
	include/keyboard_handler.h
	include/clock.h
	include/tetromino_colors.h
)

set(APP_SOURCE_FILES
	src/keyboard_handler.c
	src/clock.c
	src/tetromino_colors.c
	src/main.c
)

include_directories(${APP_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} WIN32 ${APP_SOURCE_FILES} ${APP_HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${ENGINE_NAME})

find_package(SDL2 REQUIRED)

if(SDL2_FOUND)
	include_directories( ${SDL2_INCLUDE_DIR} )
	target_link_libraries( ${PROJECT_NAME} ${SDL2_LIBRARY} )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${SDL2_PATH}/lib/${CONFIGURATION}/SDL2.dll
        ${CMAKE_CURRENT_BINARY_DIR})   