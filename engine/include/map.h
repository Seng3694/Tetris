#ifndef ENGINE_MAP_H
#define ENGINE_MAP_H

#include "common.h"
#include "tetromino.h"

#include <stdlib.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 23
#define MAP_VISIBLE_HEIGHT 20

#define TETROMINO_SPAWN_O_X (MAP_WIDTH / 2 - 1)
#define TETROMINO_SPAWN_O_Y (MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1)

#define TETROMINO_SPAWN_Z_X (MAP_WIDTH / 2 - 2)
#define TETROMINO_SPAWN_Z_Y (MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1)

#define TETROMINO_SPAWN_S_X (MAP_WIDTH / 2 - 2)
#define TETROMINO_SPAWN_S_Y (MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1)

#define TETROMINO_SPAWN_L_X (MAP_WIDTH / 2 - 2)
#define TETROMINO_SPAWN_L_Y (MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1)

#define TETROMINO_SPAWN_J_X (MAP_WIDTH / 2 - 2)
#define TETROMINO_SPAWN_J_Y (MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1)

#define TETROMINO_SPAWN_I_X (MAP_WIDTH / 2 - 2)
#define TETROMINO_SPAWN_I_Y (MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1)

#define TETROMINO_SPAWN_T_X (MAP_WIDTH / 2 - 2)
#define TETROMINO_SPAWN_T_Y (MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1)

/**
* \brief The map struct.
* \sa    Map_Create()
* \sa    Map_Destroy()
* \sa    Map_Collides()
* \sa    Map_SolidifyTetrmino()
* \sa    Map_IsInBounds()
*/
typedef struct
{
	sbyte* data;
} Map;

/**
* \brief  Creates a new map.
* \return The created map.
* \sa	  Map_Destroy()
*/
Map* Map_Create(void);

/**
* \brief	  Destroys a map.
* \param map  The map to destroy.
* \sa		  Map_Create()
*/
void Map_Destroy(Map* map);

/**
* \brief           Check if a tetromino collides with any block in the map.
* \param map       The map to check.
* \param tetromino The tetromino to check.
* \return          TRUE(1) if it does and FALSE(0) if not.
*/
bool Map_Collides(Map* map, Tetromino* tetromino);

/**
* \brief           Embeds a tetromino in the map.
* \param map       The map to embed in.
* \param tetromino The tetromino to embed.
*/
void Map_SolidifyTetrmino(Map* map, Tetromino* tetromino);

/**
* \brief           Check if a tetromino is inside the map.
* \param map       The map to check.
* \param tetromino The tetromino to check.
* \return          TRUE(1) if it does and FALSE(0) if not.
*/
bool Map_IsInBounds(Map* map, Tetromino* tetromino);

#endif
