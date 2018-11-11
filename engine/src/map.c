#include "map.h"

Map* Map_Create()
{
	Map* map = malloc(sizeof(Map));
	map->data = calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(sbyte));
	return map;
}

void Map_Destroy(Map* map)
{
	free(map->data);
	map->data = NULL;
	free(map);
	map = NULL;
}

bool Map_Collides(Map* map, Tetromino* tetromino)
{
	sbyte size = 3;
	if (tetromino->type == TETROMINO_TYPE_O)
		size = 2;
	if (tetromino->type == TETROMINO_TYPE_I)
		size = 4;

	if (!Map_IsInBounds(map, tetromino))
		return TRUE;

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			if (tetromino->data[y * size + x] != TETROMINO_TYPE_UNDEFINED)
			{
				if (map->data[(y + tetromino->y) * MAP_WIDTH + x + tetromino->x] != TETROMINO_TYPE_UNDEFINED)
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

void Map_SolidifyTetrmino(Map* map, Tetromino* tetromino) 
{
	sbyte size = 3;
	if (tetromino->type == TETROMINO_TYPE_O)
		size = 2;
	if (tetromino->type == TETROMINO_TYPE_I)
		size = 4;

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			if(tetromino->data[y * size + x] != TETROMINO_TYPE_UNDEFINED)
				map->data[(y + tetromino->y) * MAP_WIDTH + x + tetromino->x] = tetromino->data[y * size + x];
		}
	}
}

bool Map_IsInBounds(Map* map, Tetromino* tetromino)
{
	sbyte size = 3;
	if (tetromino->type == TETROMINO_TYPE_O)
		size = 2;
	if (tetromino->type == TETROMINO_TYPE_I)
		size = 4;

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			if (tetromino->data[y * size + x] != TETROMINO_TYPE_UNDEFINED)
			{
				if (tetromino->x + x < 0 || tetromino->x + x > MAP_WIDTH - 1
					|| tetromino->y + y < 0 || tetromino->y + y > MAP_HEIGHT - 1)
					return FALSE;
			}
		}
	}

	return TRUE;
}
