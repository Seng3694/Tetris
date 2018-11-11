#ifndef ENGINE_TETROMINO_H
#define ENGINE_TETROMINO_H

#include <stdlib.h>
#include <stdio.h>
#include "tetromino_type.h"
#include "common.h"

/**
* \brief The tetromino struct.
* \sa    Tetromino_Create()
* \sa    Tetromino_Destroy()
* \sa    Tetromino_RotateRight()
* \sa    Tetromino_RotateLeft()
*/
typedef struct
{
	sbyte x;
	sbyte y;
	sbyte type;
	sbyte* data;
} Tetromino;

/**
* \brief      Creates a tetromino with the given type.
* \param type The tetromino type. Following types are available:
*             TETROMINO_TYPE_O
*             TETROMINO_TYPE_Z
*             TETROMINO_TYPE_S
*             TETROMINO_TYPE_L
*             TETROMINO_TYPE_J
*             TETROMINO_TYPE_I
*             TETROMINO_TYPE_T
* \return     The created tetromino.
* \sa		  Tetromino_Destroy()
*/
Tetromino* Tetromino_Create(const sbyte type);

/**
* \brief           Destroys the tetromino.
* \param tetromino The tetromino to destroy.
* \sa              Tetromino_Create()
*/
void Tetromino_Destroy(Tetromino* tetromino);

/**
* \brief           Rotates a tetrimino 90° clockwise.
* \param tetromino The tetromino to rotate.
* \sa              Tetromino_RotateLeft()
*/
void Tetromino_RotateRight(Tetromino* tetromino);

/**
* \brief           Rotates a tetrimino 90° counter clockwise.
* \param tetromino The tetromino to rotate.
* \sa              Tetromino_RotateRight()
*/
void Tetromino_RotateLeft(Tetromino* tetromino);

#endif
