#ifndef CHRONO_H_INCLUDED
#define CHRONO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
typedef struct 
{
	Uint32 currentTime;
	Uint32 lastTime;
	int counter;
	bool pause;
    SDL_Surface *texte;
    SDL_Rect position;
    TTF_Font *police;
    SDL_Color couleur;
}Chrono;

void Init_Chrono(Chrono *c,SDL_Rect pos,int temps);
void Display_Chrono(Chrono *c,SDL_Surface*ecran);
bool Calcul_Chrono(Chrono *c);
void Pause_Chrono(Chrono *c);
bool Calcul_ChronoE(Chrono *c,SDL_Surface *ecran);



#endif
