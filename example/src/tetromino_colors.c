#include "tetromino_colors.h"

void set_tetromino_render_color(SDL_Renderer* renderer, sbyte type, byte alpha)
{
	switch (type)
	{
	case TETROMINO_TYPE_O: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_O_R, TETROMINO_COLOR_O_G, TETROMINO_COLOR_O_B, alpha); break;
	case TETROMINO_TYPE_Z: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_Z_R, TETROMINO_COLOR_Z_G, TETROMINO_COLOR_Z_B, alpha); break;
	case TETROMINO_TYPE_S: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_S_R, TETROMINO_COLOR_S_G, TETROMINO_COLOR_S_B, alpha); break;
	case TETROMINO_TYPE_L: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_L_R, TETROMINO_COLOR_L_G, TETROMINO_COLOR_L_B, alpha); break;
	case TETROMINO_TYPE_J: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_J_R, TETROMINO_COLOR_J_G, TETROMINO_COLOR_J_B, alpha); break;
	case TETROMINO_TYPE_I: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_I_R, TETROMINO_COLOR_I_G, TETROMINO_COLOR_I_B, alpha); break;
	case TETROMINO_TYPE_T: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_T_R, TETROMINO_COLOR_T_G, TETROMINO_COLOR_T_B, alpha); break;
	}
}

void set_tetromino_shadow_render_color(SDL_Renderer* renderer, sbyte type, byte alpha)
{
	switch (type)
	{
	case TETROMINO_TYPE_O: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_O_R / 2, TETROMINO_COLOR_O_G / 2, TETROMINO_COLOR_O_B / 2, alpha); break;
	case TETROMINO_TYPE_Z: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_Z_R / 2, TETROMINO_COLOR_Z_G / 2, TETROMINO_COLOR_Z_B / 2, alpha); break;
	case TETROMINO_TYPE_S: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_S_R / 2, TETROMINO_COLOR_S_G / 2, TETROMINO_COLOR_S_B / 2, alpha); break;
	case TETROMINO_TYPE_L: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_L_R / 2, TETROMINO_COLOR_L_G / 2, TETROMINO_COLOR_L_B / 2, alpha); break;
	case TETROMINO_TYPE_J: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_J_R / 2, TETROMINO_COLOR_J_G / 2, TETROMINO_COLOR_J_B / 2, alpha); break;
	case TETROMINO_TYPE_I: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_I_R / 2, TETROMINO_COLOR_I_G / 2, TETROMINO_COLOR_I_B / 2, alpha); break;
	case TETROMINO_TYPE_T: SDL_SetRenderDrawColor(renderer, TETROMINO_COLOR_T_R / 2, TETROMINO_COLOR_T_G / 2, TETROMINO_COLOR_T_B / 2, alpha); break;
	}
}