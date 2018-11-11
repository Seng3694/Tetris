set(ENGINE_INCLUDE_DIRS
	include
)

set(ENGINE_HEADER_FILES
	include/common.h
	include/tetromino.h
	include/tetromino_type.h
	include/map.h
	include/tetris.h
	include/tetris_action.h
	include/spawn_bag.h
	include/tetris_speedcurve.h
)

set(ENGINE_SOURCE_FILES
	src/tetromino.c
	src/spawn_bag.c
	src/map.c
	src/tetris.c
	src/tetris_speedcurve.c
)

include_directories(${ENGINE_INCLUDE_DIRS})

add_library(${ENGINE_NAME} ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES})
