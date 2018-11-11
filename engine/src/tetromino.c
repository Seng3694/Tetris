#include "tetromino.h"

Tetromino* Tetromino_Create(const sbyte type)
{
	Tetromino* tetromino = malloc(sizeof(Tetromino));
	tetromino->type = type;

	switch (type)
	{
	case TETROMINO_TYPE_I:
		tetromino->data = calloc(16, sizeof(sbyte));
		tetromino->data[4] = TETROMINO_TYPE_I;
		tetromino->data[5] = TETROMINO_TYPE_I;
		tetromino->data[6] = TETROMINO_TYPE_I;
		tetromino->data[7] = TETROMINO_TYPE_I;
		break;
	case TETROMINO_TYPE_O:
		tetromino->data = calloc(4, sizeof(sbyte));
		tetromino->data[0] = TETROMINO_TYPE_O;
		tetromino->data[1] = TETROMINO_TYPE_O;
		tetromino->data[2] = TETROMINO_TYPE_O;
		tetromino->data[3] = TETROMINO_TYPE_O;
		break;
	case TETROMINO_TYPE_J:
		tetromino->data = calloc(9, sizeof(sbyte));
		tetromino->data[0] = TETROMINO_TYPE_J;
		tetromino->data[3] = TETROMINO_TYPE_J;
		tetromino->data[4] = TETROMINO_TYPE_J;
		tetromino->data[5] = TETROMINO_TYPE_J;
		break;
	case TETROMINO_TYPE_L:
		tetromino->data = calloc(9, sizeof(sbyte));
		tetromino->data[2] = TETROMINO_TYPE_L;
		tetromino->data[3] = TETROMINO_TYPE_L;
		tetromino->data[4] = TETROMINO_TYPE_L;
		tetromino->data[5] = TETROMINO_TYPE_L;
		break;
	case TETROMINO_TYPE_S:
		tetromino->data = calloc(9, sizeof(sbyte));
		tetromino->data[1] = TETROMINO_TYPE_S;
		tetromino->data[2] = TETROMINO_TYPE_S;
		tetromino->data[3] = TETROMINO_TYPE_S;
		tetromino->data[4] = TETROMINO_TYPE_S;
		break;
	case TETROMINO_TYPE_Z:
		tetromino->data = calloc(9, sizeof(sbyte));
		tetromino->data[0] = TETROMINO_TYPE_Z;
		tetromino->data[1] = TETROMINO_TYPE_Z;
		tetromino->data[4] = TETROMINO_TYPE_Z;
		tetromino->data[5] = TETROMINO_TYPE_Z;
		break;
	case TETROMINO_TYPE_T:
		tetromino->data = calloc(9, sizeof(sbyte));
		tetromino->data[1] = TETROMINO_TYPE_T;
		tetromino->data[3] = TETROMINO_TYPE_T;
		tetromino->data[4] = TETROMINO_TYPE_T;
		tetromino->data[5] = TETROMINO_TYPE_T;
		break;
	}

	return tetromino;
}

void Tetromino_Destroy(Tetromino* tetromino)
{
	free(tetromino->data);
	tetromino->data = NULL;
	
	free(tetromino);
	tetromino = NULL;
}

void Tetromino_RotateRight(Tetromino* tetromino)
{
	/*
	0 1 2 
	3 4 5
	6 7 9

	6 3 0
	7 4 1
	9 5 2

	0 1 2 3
	4 5 6 7
	8 9 A B
	C D E F

	C 8 4 0
	D 9 5 1
	E A 6 2
	F B 7 3
	*/

	if (tetromino->type == TETROMINO_TYPE_O)
		return;

	sbyte size = 3;

	if(tetromino->type == TETROMINO_TYPE_I)
		size = 4;
	
	sbyte* newArray = calloc(size * size, sizeof(sbyte));

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			newArray[x * size + size - y - 1] = tetromino->data[y * size + x];
		}
	}

	free(tetromino->data);
	tetromino->data = newArray;
}

void Tetromino_RotateLeft(Tetromino* tetromino)
{
	/*
	0 1 2 
	3 4 5
	6 7 9

	2 5 9
	1 4 7
	0 3 6

	0 1 2 3
	4 5 6 7
	8 9 A B
	C D E F

	3 7 B F
	2 6 A E
	1 5 9 D
	0 4 8 C
	*/

	if (tetromino->type == TETROMINO_TYPE_O)
		return;

	sbyte size = 3;

	if (tetromino->type == TETROMINO_TYPE_I)
		size = 4;

	sbyte* newArray = calloc(size * size, sizeof(sbyte));

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			newArray[(size - x - 1) * size + y] = tetromino->data[y * size + x];
		}
	}

	free(tetromino->data);
	tetromino->data = newArray;
}
