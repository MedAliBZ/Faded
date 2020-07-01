#ifndef SCROL_H_INCLUDED
#define SCROL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


typedef struct
{
	SDL_Rect scroll;
	SDL_Rect pos_real;
}Scroll;

void Initialisation_Scroll(Scroll *cam,SDL_Rect pos_player,int width,int height);
void Scrolling(Scroll *cam,SDL_Rect pos_player,int width,int height);


#endif
