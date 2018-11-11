#ifndef ENGINE_TETRIS_SPEEDCURVE_H
#define ENGINE_TETRIS_SPEEDCURVE_H

#include "common.h"
#include <math.h>

/**
* \brief       Calculates the tick time for a tetris game in seconds for any level.
* Formula taken from: http://tetris.wikia.com/wiki/Tetris_Worlds .
* \param level The level (1-15)
* \return      The tick time in seconds.
*/
float get_tetris_speed_time(const byte level);

#endif
