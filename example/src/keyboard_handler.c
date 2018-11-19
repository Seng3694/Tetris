#include "keyboard_handler.h"

KeyboardHandler* KeyboardHandler_Create(void)
{
	KeyboardHandler* handler = malloc(sizeof(KeyboardHandler));
	handler->keyDownDelayElapsed = 0;
	memset(handler->keystates, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memset(handler->before, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	return handler;
}

void KeyboardHandler_Destroy(KeyboardHandler* handler)
{
	free(handler);
}

void KeyboardHandler_HandleEvent(KeyboardHandler* handler, const SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
	{
		handler->keystates[event->key.keysym.scancode] = event->key.state;
	}
}

void KeyboardHandler_Update(KeyboardHandler* handler)
{
	memcpy(&handler->before, &handler->keystates, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(&handler->keystates, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

bool KeyboardHandler_IsKeyPressed(KeyboardHandler* handler, const SDL_Scancode key)
{
	return handler->keystates[key] == SDL_PRESSED
		&& handler->before[key] == SDL_RELEASED;
}

bool KeyboardHandler_IsKeyReleased(KeyboardHandler* handler, const SDL_Scancode key)
{
	return handler->keystates[key] == SDL_RELEASED
		&& handler->before[key] == SDL_PRESSED;
}

bool KeyboardHandler_IsKeyDown(KeyboardHandler* handler, const SDL_Scancode key, float dt)
{
	if (handler->keystates[key] == SDL_PRESSED
		&& handler->before[key] == SDL_RELEASED)
	{
		handler->keyDownDelayElapsed = 0;
		return TRUE;
	}
	else if (handler->keystates[key] == SDL_PRESSED
		&& handler->before[key] == SDL_PRESSED)
	{
		handler->keyDownDelayElapsed += dt;
		if (handler->keyDownDelayElapsed >= KEY_DOWN_DELAY)
		{
			handler->keyDownDelayElapsed = 0;
			return TRUE;
		}
	}

	return FALSE;
}