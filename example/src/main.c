#include "tetris.h"
#include "keyboard_handler.h"
#include "tetromino_colors.h"
#include "clock.h"

#include <SDL.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0, &mode);
	SDL_Window* window = SDL_CreateWindow("Tetris", 0, 0, 320, 640, SDL_WINDOW_SHOWN);
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	SDL_SetWindowPosition(window, mode.w / 2 - windowWidth / 2, mode.h / 2 - windowHeight / 2);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);
	SDL_bool isRunning = SDL_TRUE;
	SDL_Event event;

	SDL_Rect rect = { 0, 0, 32, 32 };

	Tetris* tetris = Tetris_Create();
	sbyte tetrominoSize = 3;
	sbyte type = TETROMINO_TYPE_UNDEFINED;
	KeyboardHandler* keyHandler = KeyboardHandler_Create();
	Clock* clock = Clock_Create();
	float dt = 0;

	while (isRunning && tetris->gameOver == FALSE)
	{
		Clock_Update(clock);
		dt = Clock_GetDeltaTime(clock);
		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = SDL_FALSE;
				break;
			}
		}

		KeyboardHandler_Update(keyHandler);

		if (KeyboardHandler_IsKeyDown(keyHandler, SDL_SCANCODE_LEFT, dt)
			|| KeyboardHandler_IsKeyDown(keyHandler, SDL_SCANCODE_A, dt))
			Tetris_DoAction(tetris, TETRIS_ACTION_MOVE_LEFT);

		if (KeyboardHandler_IsKeyDown(keyHandler, SDL_SCANCODE_RIGHT, dt)
			|| KeyboardHandler_IsKeyDown(keyHandler, SDL_SCANCODE_D, dt))
			Tetris_DoAction(tetris, TETRIS_ACTION_MOVE_RIGHT);

		if (KeyboardHandler_IsKeyDown(keyHandler, SDL_SCANCODE_DOWN, dt)
			|| KeyboardHandler_IsKeyDown(keyHandler, SDL_SCANCODE_S, dt))
			Tetris_DoAction(tetris, TETRIS_ACTION_MOVE_DOWN);

		if (KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_UP)
			|| KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_W))
			Tetris_DoAction(tetris, TETRIS_ACTION_HARD_DROP);

		if (KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_1)
			|| KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_KP_1))
			Tetris_DoAction(tetris, TETRIS_ACTION_ROTATE_LEFT);

		if (KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_2)
			|| KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_KP_2))
			Tetris_DoAction(tetris, TETRIS_ACTION_ROTATE_RIGHT);

		if (KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_4)
			|| KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_KP_4)
			|| KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_5)
			|| KeyboardHandler_IsKeyPressed(keyHandler, SDL_SCANCODE_KP_5))
			Tetris_DoAction(tetris, TETRIS_ACTION_HOLD);
		
		if (KeyboardHandler_IsKeyReleased(keyHandler, SDL_SCANCODE_ESCAPE))
			isRunning = SDL_FALSE;

		Tetris_Update(tetris, dt);

		SDL_SetRenderDrawColor(renderer, 0x10, 0x10, 0x10, 0xff);
		SDL_RenderClear(renderer);
		
		int yOffset = MAP_HEIGHT - MAP_VISIBLE_HEIGHT;
		tetrominoSize = 3;
		if (tetris->current->type == TETROMINO_TYPE_O)
			tetrominoSize = 2;
		if (tetris->current->type == TETROMINO_TYPE_I)
			tetrominoSize = 4;

		for (int y = 0; y < tetrominoSize; ++y)
		{
			for (int x = 0; x < tetrominoSize; ++x)
			{
				if (tetris->current->data[y * tetrominoSize + x] != TETROMINO_TYPE_UNDEFINED)
				{
					set_tetromino_shadow_render_color(renderer, tetris->current->type, 255);
					rect.x = (tetris->shadow->x + x) * rect.w;
					rect.y = (tetris->shadow->y + y - yOffset) * rect.h;
					SDL_RenderFillRect(renderer, &rect);

					set_tetromino_render_color(renderer, tetris->current->type, 255);
					rect.x = (tetris->current->x + x) * rect.w;
					rect.y = (tetris->current->y + y - yOffset) * rect.h;
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}

		type = TETROMINO_TYPE_UNDEFINED;

		for (int y = 0; y < MAP_HEIGHT; ++y)
		{
			for (int x = 0; x < MAP_WIDTH; ++x)
			{
				rect.x = (x * rect.w);
				rect.y = (y * rect.h);

				type = tetris->map->data[(y + yOffset) * MAP_WIDTH + x];
				
				if(type != TETROMINO_TYPE_UNDEFINED)
				{
					set_tetromino_render_color(renderer, type, 255);
					SDL_RenderFillRect(renderer, &rect);
				}

				SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0x20);
				SDL_RenderDrawRect(renderer, &rect);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	Clock_Destroy(clock);
	KeyboardHandler_Destroy(keyHandler);
	Tetris_Destroy(tetris);
	return 0;
}
