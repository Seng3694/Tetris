#include "tetris.h"

Tetris* Tetris_Create(void)
{
	Tetris* tetris = malloc(sizeof(Tetris));
	tetris->lockElapsed = 0;
	tetris->lockInterrupts = 0;
	tetris->score = 0;
	tetris->elapsedSinceLastTick = 0;
	tetris->level = 1;
	tetris->wasHoldSpawned = FALSE;
	tetris->isLocking = FALSE;
	tetris->gameOver = FALSE;
	tetris->hold = TETROMINO_TYPE_UNDEFINED;
	tetris->current = NULL;
	tetris->shadow = NULL;
	tetris->map = Map_Create();
	tetris->bag = SpawnBag_Create();
	Tetris_Spawn(tetris, SpawnBag_GetNext(tetris->bag));
	Tetris_UpdateShadow(tetris);
	return tetris;
}

void Tetris_Destroy(Tetris* tetris)
{
	if (tetris->map)
	{
		free(tetris->map);
		tetris->map = NULL;
	}

	if (tetris->current)
	{
		free(tetris->current);
		tetris->current = NULL;
	}

	if (tetris->shadow)
	{
		free(tetris->shadow);
		tetris->shadow = NULL;
	}

	free(tetris);
	tetris = NULL;
}

void Tetris_Update(Tetris* tetris, const float dt)
{
	tetris->elapsedSinceLastTick += dt;
	if (tetris->elapsedSinceLastTick >= get_tetris_speed_time(tetris->level))
	{
		tetris->elapsedSinceLastTick = 0;
		Tetris_Tick(tetris);
	}

	if (tetris->isLocking == TRUE)
	{
		tetris->lockElapsed += dt;
		if (tetris->lockElapsed >= LOCK_DELAY)
		{
			tetris->lockElapsed = 0;
			tetris->isLocking = FALSE;
			Tetris_SolidifyTetromino(tetris);
			Tetris_Spawn(tetris, SpawnBag_GetNext(tetris->bag));
		}
	}
}

void Tetris_Tick(Tetris* tetris)
{
	Tetris_DoAction(tetris, TETRIS_ACTION_TICK_DOWN);
}

void Tetris_DoAction(Tetris* tetris, const sbyte action)
{
	switch (action)
	{
	case TETRIS_ACTION_MOVE_LEFT:
		tetris->current->x--;
		if (Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x++;
		}
		else
		{
			Tetris_LockInterrupt(tetris);
		}
		break;
	case TETRIS_ACTION_MOVE_RIGHT:
		tetris->current->x++;
		if (Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x--; 
		}
		else
		{
			Tetris_LockInterrupt(tetris);
		}
		break;
	case TETRIS_ACTION_MOVE_DOWN:
		if (!tetris->isLocking)
		{
			tetris->current->y++;
			if (Map_Collides(tetris->map, tetris->current))
			{
				tetris->current->y--;
				tetris->isLocking = TRUE;
			}
		}
		else
		{
			Tetris_SolidifyTetromino(tetris);
			Tetris_Spawn(tetris, SpawnBag_GetNext(tetris->bag));
		}
		
		break;
	case TETRIS_ACTION_TICK_DOWN:
		tetris->current->y++;
		if (Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->y--;
			tetris->isLocking = TRUE;
		}
		break;
	case TETRIS_ACTION_ROTATE_LEFT:
		Tetromino_RotateLeft(tetris->current);

		//if it is colliding or out of bounds move 1 left
		if (!Map_IsInBounds(tetris->map, tetris->current)
			|| Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x--;
		}
		//if it still does move 1 right
		if (!Map_IsInBounds(tetris->map, tetris->current)
			|| Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x += 2;
		}
		//if it still does reset => rotation not possible
		if (!Map_IsInBounds(tetris->map, tetris->current)
			|| Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x -= 1;
			Tetromino_RotateRight(tetris->current);
		}
		else
		{
			Tetromino_RotateLeft(tetris->shadow); 
			Tetris_LockInterrupt(tetris);
		}

		break;
	case TETRIS_ACTION_ROTATE_RIGHT:
		Tetromino_RotateRight(tetris->current);

		//if it is colliding or out of bounds move 1 left
		if (!Map_IsInBounds(tetris->map, tetris->current)
			|| Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x--;
		}
		//if it still does move 1 right
		if (!Map_IsInBounds(tetris->map, tetris->current)
			|| Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x += 2;
		}
		//if it still does reset => rotation not possible
		if (!Map_IsInBounds(tetris->map, tetris->current)
			|| Map_Collides(tetris->map, tetris->current))
		{
			tetris->current->x -= 1;
			Tetromino_RotateLeft(tetris->current);
		}
		else
		{
			Tetromino_RotateRight(tetris->shadow);
			Tetris_LockInterrupt(tetris);
		}

		break;
	case TETRIS_ACTION_HARD_DROP:
		do
		{
			tetris->current->y++;
		} while (!Map_Collides(tetris->map, tetris->current));

		tetris->current->y--;
		Tetris_SolidifyTetromino(tetris);
		Tetris_Spawn(tetris, SpawnBag_GetNext(tetris->bag));

		break;
	case TETRIS_ACTION_HOLD:
		if (tetris->hold != TETROMINO_TYPE_UNDEFINED)
		{
			if (tetris->wasHoldSpawned == FALSE)
			{
				tetris->wasHoldSpawned = TRUE;
				sbyte holdType = tetris->hold;
				tetris->hold = tetris->current->type;
				Tetris_Spawn(tetris, holdType);
			}
		}
		else
		{
			tetris->hold = tetris->current->type;
			Tetris_Spawn(tetris, SpawnBag_GetNext(tetris->bag));
		}
		
		break;
	}

	Tetris_UpdateShadow(tetris);
}

void Tetris_LockInterrupt(Tetris* tetris)
{
	if (tetris->isLocking && tetris->lockInterrupts < LOCK_INTERRUPT_LIMIT)
	{
		tetris->lockInterrupts++;
		tetris->lockElapsed = 0;
	}
}
void Tetris_UpdateShadow(Tetris* tetris)
{
	tetris->shadow->y = tetris->current->y;
	tetris->shadow->x = tetris->current->x;

	do
	{
		tetris->shadow->y++;
	} while (!Map_Collides(tetris->map, tetris->shadow));

	tetris->shadow->y--;
}

void Tetris_SolidifyTetromino(Tetris* tetris)
{
	Map_SolidifyTetrmino(tetris->map, tetris->current);
	Tetris_SolveRows(tetris);
	tetris->lockInterrupts = 0;
	tetris->lockElapsed = 0;
	tetris->isLocking = FALSE;
	tetris->lockElapsed = 0;
	tetris->wasHoldSpawned = FALSE;

	for (int y = 0; y < MAP_HEIGHT - MAP_VISIBLE_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			if (tetris->map->data[y * MAP_WIDTH + x] != TETROMINO_TYPE_UNDEFINED)
				tetris->gameOver = TRUE;
		}
	}
}

sbyte Tetris_SolveRows(Tetris* tetris)
{
	sbyte solved = 0;
	bool isFull = TRUE;

	for (int y = MAP_HEIGHT - 1; y > MAP_HEIGHT - MAP_VISIBLE_HEIGHT - 1; --y)
	{
		isFull = TRUE;

		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			if (tetris->map->data[y * MAP_WIDTH + x] == TETROMINO_TYPE_UNDEFINED)
				isFull = FALSE;
		}

		if (isFull == TRUE)
		{
			++solved;
			memcpy((tetris->map->data + MAP_WIDTH), tetris->map->data, y * MAP_WIDTH);
			y++;
		}
	}

	return solved;
}

void Tetris_Spawn(Tetris* tetris, const sbyte type)
{
	if (tetris->current)
		free(tetris->current);
	if (tetris->shadow)
		free(tetris->shadow);

	tetris->current = Tetromino_Create(type);

	switch (type)
	{
	case TETROMINO_TYPE_O:
		tetris->current->x = TETROMINO_SPAWN_O_X;
		tetris->current->y = TETROMINO_SPAWN_O_Y;
		break;
	case TETROMINO_TYPE_Z:
		tetris->current->x = TETROMINO_SPAWN_Z_X;
		tetris->current->y = TETROMINO_SPAWN_Z_Y;
		break;
	case TETROMINO_TYPE_S:
		tetris->current->x = TETROMINO_SPAWN_S_X;
		tetris->current->y = TETROMINO_SPAWN_S_Y;
		break;
	case TETROMINO_TYPE_L:
		tetris->current->x = TETROMINO_SPAWN_L_X;
		tetris->current->y = TETROMINO_SPAWN_L_Y;
		break;
	case TETROMINO_TYPE_J:
		tetris->current->x = TETROMINO_SPAWN_J_X;
		tetris->current->y = TETROMINO_SPAWN_J_Y;
		break;
	case TETROMINO_TYPE_I:
		tetris->current->x = TETROMINO_SPAWN_I_X;
		tetris->current->y = TETROMINO_SPAWN_I_Y;
		break;
	case TETROMINO_TYPE_T:
		tetris->current->x = TETROMINO_SPAWN_T_X;
		tetris->current->y = TETROMINO_SPAWN_T_Y;
		break;
	}

	tetris->shadow = Tetromino_Create(type);
	Tetris_UpdateShadow(tetris);
}
