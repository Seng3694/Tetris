#ifndef APP_TETROMINO_COLORS_H
#define APP_TETROMINO_COLORS_H

#include <SDL.h>
#include "common.h"
#include "tetromino_type.h"

#define TETROMINO_COLOR_I_R 0x2D
#define TETROMINO_COLOR_I_G 0xC8
#define TETROMINO_COLOR_I_B 0xEF

#define TETROMINO_COLOR_J_R 0x00
#define TETROMINO_COLOR_J_G 0x00
#define TETROMINO_COLOR_J_B 0xFF

#define TETROMINO_COLOR_L_R 0xEF
#define TETROMINO_COLOR_L_G 0x7A
#define TETROMINO_COLOR_L_B 0x1B

#define TETROMINO_COLOR_O_R 0xF7
#define TETROMINO_COLOR_O_G 0xD4
#define TETROMINO_COLOR_O_B 0x02

#define TETROMINO_COLOR_S_R 0x00
#define TETROMINO_COLOR_S_G 0xFF
#define TETROMINO_COLOR_S_B 0x00

#define TETROMINO_COLOR_T_R 0xAF
#define TETROMINO_COLOR_T_G 0x4C
#define TETROMINO_COLOR_T_B 0x9D

#define TETROMINO_COLOR_Z_R 0xFF
#define TETROMINO_COLOR_Z_G 0x00
#define TETROMINO_COLOR_Z_B 0x00

void set_tetromino_render_color(SDL_Renderer* renderer, sbyte type, byte alpha);
void set_tetromino_shadow_render_color(SDL_Renderer* renderer, sbyte type, byte alpha);

#endif