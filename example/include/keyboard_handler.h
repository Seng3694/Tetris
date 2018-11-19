#ifndef APP_KEYBOARD_HANDLER_H
#define APP_KEYBOARD_HANDLER_H

#include <SDL.h>
#include <string.h>
#include "common.h"

#define KEY_DOWN_DELAY 0.13

typedef struct
{
	float keyDownDelayElapsed;
	Uint8 keystates[SDL_NUM_SCANCODES];
	Uint8 before[SDL_NUM_SCANCODES];
} KeyboardHandler;

KeyboardHandler* KeyboardHandler_Create(void);
void KeyboardHandler_Destroy(KeyboardHandler* handler);

void KeyboardHandler_HandleEvent(KeyboardHandler* handler, const SDL_Event* event);
void KeyboardHandler_Update(KeyboardHandler* handler);

bool KeyboardHandler_IsKeyPressed(KeyboardHandler* handler, const SDL_Scancode key);
bool KeyboardHandler_IsKeyReleased(KeyboardHandler* handler, const SDL_Scancode key);
bool KeyboardHandler_IsKeyDown(KeyboardHandler* handler, const SDL_Scancode key, float dt);

#endif