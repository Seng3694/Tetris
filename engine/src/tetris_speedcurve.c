#include "tetris_speedcurve.h"

float get_tetris_speed_time(const byte level)
{
	return pow((0.8 - ((level - 1) * 0.007)), (level - 1));
}
