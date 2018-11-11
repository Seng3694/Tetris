#include "clock.h"

Clock* Clock_Create()
{
	Clock* clock = malloc(sizeof(Clock));
	clock->last = 0;
	clock->now = SDL_GetPerformanceCounter();
	return clock;
}

void Clock_Destroy(Clock* clock)
{
	free(clock);
}

void Clock_Update(Clock* clock)
{
	clock->last = clock->now;
	clock->now = SDL_GetPerformanceCounter();
}

float Clock_GetDeltaTime(Clock* clock)
{
	return (float)((clock->now - clock->last) / (double)SDL_GetPerformanceFrequency());
}