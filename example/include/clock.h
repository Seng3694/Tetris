#ifndef APP_CLOCK_H
#define APP_CLOCK_H

#include <SDL.h>
#include <string.h>
#include "common.h"

typedef struct
{
	Uint64 now;
	Uint64 last;
} Clock;

Clock* Clock_Create();
void Clock_Destroy(Clock* clock);

void Clock_Update(Clock* clock);
float Clock_GetDeltaTime(Clock* clock);

#endif