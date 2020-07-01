#ifndef SAVEGAME_H_INCLUDED
#define SAVEGAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


typedef struct SaveG
{
	SDL_Surface *back;
    SDL_Surface *boutons[2];
    SDL_Surface *boutonsp[2];
    SDL_Rect yes,no;
    SDL_Rect posBlit;
    int image_courrante;
}SaveG;

void Init_Save(SaveG *s);
void Display_Save(SaveG *s,SDL_Surface*ecran);





#endif
