#ifndef ENGINE_TETRIS_H
#define ENGINE_TETRIS_H

#include <string.h>
#include <time.h>
#include "tetromino.h"
#include "tetris_action.h"
#include "map.h"
#include "common.h"
#include "spawn_bag.h"
#include "tetris_speedcurve.h"

#define LOCK_DELAY 0.5
#define LOCK_INTERRUPT_LIMIT 15

/**
* \brief Core struct of a tetris game.
* \sa    Tetris_Create()
* \sa    Tetris_Destroy()
* \sa    Tetris_Update()
* \sa    Tetris_Tick()
* \sa    Tetris_DoAction()
* \sa    Tetris_UpdateShadow()
* \sa    Tetris_LockInterrupt()
* \sa    Tetris_SolidifyTetromino()
* \sa    Tetris_SolveRows()
* \sa    Tetris_Spawn()
*/
typedef struct
{
	bool isLocking;
	float lockElapsed;
	sbyte lockInterrupts;

	sbyte hold;
	bool wasHoldSpawned;

	byte level;
	float elapsedSinceLastTick;
	uint score;
	bool gameOver;

	SpawnBag* bag;
	Tetromino* current;
	Tetromino* shadow;
	Map* map;
} Tetris;

/**
* \brief  Creates a new tetris game.
* \return The created tetris game.
* \sa     Tetris_Destroy()
*/
Tetris* Tetris_Create();

/**
* \brief        Destroys the tetris game.
* \param tetris The tetris game to destroy.
* \sa           Tetris_Create()
*/
void Tetris_Destroy(Tetris* tetris);

/**
* \brief        Updates timers for locking and ticking.
* \param tetris The tetris game to update.
* \param dt     The delta time.
*/
void Tetris_Update(Tetris* tetris, const float dt);

/**
* \brief        Moves the current tetromino one down.
* This method will be triggered by Tetris_Update() automatically.
* \param tetris The tetris game.
* \sa           Tetris_Update()
*/
void Tetris_Tick(Tetris* tetris);

/**
* \brief        Executes the specific action.
* This method will be triggered by Tetris_Update() automatically.
* \param tetris The tetris game.
* \param action The action code. Following actions are available:
*               TETRIS_ACTION_MOVE_LEFT
*               TETRIS_ACTION_MOVE_RIGHT
*               TETRIS_ACTION_MOVE_DOWN
*               TETRIS_ACTION_ROTATE_LEFT 
*               TETRIS_ACTION_ROTATE_RIGHT
*               TETRIS_ACTION_HARD_DROP
*               TETRIS_ACTION_HOLD
*               TETRIS_ACTION_TICK_DOWN
*/
void Tetris_DoAction(Tetris* tetris, const sbyte action);

/**
* \brief	    Updates the shadow tetrominos position.
* \param tetris The tetris game to update.
*/
void Tetris_UpdateShadow(Tetris* tetris);

/**
* \brief        Interrupts the current lock timer.
* Lock timer starts when a block is touching the floor and can't move down anymore.
* Everytime you move or rotate the block, the lock timer resets. The interruption is capped at LOCK_INTERRUPT_LIMIT.
* If the block won't get interrupted for LOCK_DELAY it will be solidified.
* \param tetris The tetris game to interrupt.
* \sa			Tetris_SolidifyTetromino()
*/
void Tetris_LockInterrupt(Tetris* tetris);

/**
* \brief        Embeds the current tetromino in to the map.
* \param tetris The tetris game.
* \sa		    Map_SolidifyTetromino()
*/
void Tetris_SolidifyTetromino(Tetris* tetris);

/**
* \brief        Solves any full row and rearranges the map.
* \param tetris The tetris game.
* \return		Count of lines solved
*/
sbyte Tetris_SolveRows(Tetris* tetris);

/**
* \brief        Spawns a tetromino and shadow of the given type.
* \param tetris The tetris game.
* \param type   The tetromino type. Following types are available:
*               TETROMINO_TYPE_O
*               TETROMINO_TYPE_Z
*               TETROMINO_TYPE_S
*               TETROMINO_TYPE_L
*               TETROMINO_TYPE_J
*               TETROMINO_TYPE_I
*               TETROMINO_TYPE_T
*/
void Tetris_Spawn(Tetris* tetris, const sbyte type);

#endif
