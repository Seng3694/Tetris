#include "spawn_bag.h"


SpawnBag* SpawnBag_Create(void)
{
	SpawnBag* bag = malloc(sizeof(SpawnBag));
	bag->index = 0;
	srand((unsigned int)time(0));
	SpawnBag_Refill(bag);
	return bag;
}

void SpawnBag_Destroy(SpawnBag* bag)
{
	free(bag);
}

void SpawnBag_Refill(SpawnBag* bag)
{
	//generate array with each type once
	for (int i = 0; i < TETROMINO_TYPE_COUNT; ++i)
	{
		bag->data[i] = i + 1;
	}

	byte rand1 = 0;
	byte rand2 = 0;

	//shuffle them by swapping random indices
	for (int i = 0; i < TETROMINO_TYPE_COUNT; ++i)
	{
		rand1 = rand() % TETROMINO_TYPE_COUNT;
		while (rand2 == rand1)
			rand2 = rand() % TETROMINO_TYPE_COUNT;

		//perform xor swap
		bag->data[rand1] ^= bag->data[rand2];
		bag->data[rand2] ^= bag->data[rand1];
		bag->data[rand1] ^= bag->data[rand2];
	}
}

sbyte SpawnBag_GetNext(SpawnBag* bag)
{
	if (bag->index >= TETROMINO_TYPE_COUNT)
	{
		bag->index = 0;
		SpawnBag_Refill(bag);
	}

	return bag->data[bag->index++];
}
