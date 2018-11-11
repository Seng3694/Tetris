#ifndef ENGINE_SPAWN_BAG_H
#define ENGINE_SPAWN_BAG_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tetromino_type.h"
#include "common.h"

/**
* \brief A struct which holds 7 different tetromino types in a random order.
* http://tetris.wikia.com/wiki/Random_Generator
* \sa    SpawnBag_Create()
* \sa    SpawnBag_Destroy()
* \sa    SpawnBag_Refill()
* \sa    SpawnBag_GetNext()
*/
typedef struct
{
	sbyte data[TETROMINO_TYPE_COUNT];
	byte index;
} SpawnBag;

/**
* \brief  Creates a new bag.
* \return The created bag.
* \sa     SpawnBag_Destroy()
*/
SpawnBag* SpawnBag_Create();

/**
* \brief      Destroys a new bag.
* \param bag  The bag to destroy.
* \sa         SpawnBag_Create()
*/
void SpawnBag_Destroy(SpawnBag* bag);

/**
* \brief      Refills the bag with the 7 different types in a random order.
* \param bag  The bag to refill.
*/
void SpawnBag_Refill(SpawnBag* bag);

/**
* \brief      Returns the next type from the bag.
* If there are no more types left, SpawnBag_Refill() will be called to generate new ones.
* \param bag  The bag to refill.
* \return     A tetromino type.
* \sa SpawnBag_Refill()
*/
sbyte SpawnBag_GetNext(SpawnBag* bag);


#endif
